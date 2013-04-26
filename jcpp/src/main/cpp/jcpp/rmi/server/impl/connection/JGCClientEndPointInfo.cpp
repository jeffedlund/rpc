#include "JGCClientEndPointInfo.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
#include "JSystem.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JGCClientEndPointInfoClass : public JClass{
                      public:
                        JGCClientEndPointInfoClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.GCClientEndPointInfo";//TODO
                            this->name="jcpp.rmi.server.impl.connection.GCClientEndPointInfo";
                            this->simpleName="GCClientEndPointInfo";
                            addInterface(JRunnable::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JGCClientEndPointInfo::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGCClientEndPointInfoClass();
                        }
                        return clazz;
                    }

                    JGCClientEndPointInfo::JGCClientEndPointInfo(JGCClient* gcClient,JServer* localServer,JEndPoint* remoteEndPoint){
                        this->gcClient=gcClient;
                        this->localServer=localServer;
                        this->remoteEndPoint = remoteEndPoint;
                        this->objects = new map<JString*, JObject*,JString::POINTER_COMPARATOR>();
                        this->gc = dynamic_cast<JIGC*>(localServer->lookup(remoteEndPoint, JIGC::getClazz()));
                        this->bIsRunning = false;
                        this->connections = localServer->getObjectInformations()->getTransport()->getConnections(remoteEndPoint);
                    }

                    void JGCClientEndPointInfo::doExport(JString* id, JObject* object){
                        lock();
                        if (objects->size() == 0) {
                            scheduledFuture = localServer->getScheduledExecutorService()->schedule(this, localServer->getConnectionConfiguration()->getGcClientTimeout()->get(),localServer->getConnectionConfiguration()->getGcClientTimeout()->get());
                        }
                        objects->insert(pair<JString*,JObject*>(id, object));
                        unlock();
                    }

                    void JGCClientEndPointInfo::unexport(JString* id){
                        lock();
                        objects->erase(id);
                        if (objects->size() == 0) {
                            unexport();
                        }
                        unlock();
                    }

                    bool JGCClientEndPointInfo::ping(){
                        bool bresult=true;
                        throwable = NULL;
                        lock();
                        JPrimitiveArray* idsArray = new JPrimitiveArray(JString::getClazz(),objects->size());
                        map<JString*,JObject*,JString::POINTER_COMPARATOR>::iterator it=objects->begin();
                        int i=0;
                        for (;it!=objects->end();it++){
                            idsArray->set(i,(*it).first);
                            i++;
                        }
                        unlock();
                        JPrimitiveArray* ping = NULL;
                        try {
                            ping = gc->ping(localServer->getEndPoint(), idsArray);
                        } catch (JThrowable* e) {
                            throwable = e;
                            if (++gcExceptionCount >= localServer->getConnectionConfiguration()->getGcClientExceptionThreshold()->get()) {
                                unexport();
                                bresult=false;
                            }
                            bresult=true;
                        }
                        gcExceptionCount = 0;
                        if (ping!=NULL){
                            for (i = 0; i < ping->size(); i++) {
                                JPrimitiveBoolean* b=(JPrimitiveBoolean*)ping->get(i);
                                if (b==NULL || !b->get()) {
                                    unexport((JString*)idsArray->get(i));
                                }
                            }
                        }
                        lock();
                        if (objects->size() == 0) {
                            bresult=false;
                        }
                        unlock();
                        return bresult;
                    }

                    void JGCClientEndPointInfo::unexport(){
                        lock();
                        gcClient->remove(remoteEndPoint);
                        if (future != NULL) {
                            future->cancel();
                            delete future;
                        }
                        scheduledFuture->cancel();
                        delete scheduledFuture;
                        unlock();
                    }

                    bool JGCClientEndPointInfo::isRunning(){
                        bool b;
                        lock();
                        b=this->bIsRunning;
                        unlock();
                        return b;
                    }

                    void JGCClientEndPointInfo::setRunning(bool b){
                        lock();
                        this->bIsRunning=b;
                        unlock();
                    }

                    vector<JObject*>* JGCClientEndPointInfo::getObjects(){
                        lock();
                        vector<JObject*>* vec=getValues(objects);
                        unlock();
                        return vec;
                    }

                    void JGCClientEndPointInfo::run(){
                        if (!isRunning()) {//TODO later put in a executorservice.submit(runnable{ping})
                            setRunning(true);
                            bool bping = ping();
                            vector<JObject*>* values=getObjects();
                            if (!bping) {
                                if (gcExceptionCount == 0) {
                                    gcClient->getGCClientListener()->objectDead(remoteEndPoint, values);
                                } else {
                                    gcClient->getGCClientListener()->objectDead(remoteEndPoint, values,throwable);
                                }
                            } else {
                                if (gcExceptionCount == 0) {
                                    gcClient->getGCClientListener()->objectAlive(remoteEndPoint, values);
                                } else {
                                    gcClient->getGCClientListener()->objectMaybeDead(remoteEndPoint, values, throwable);
                                }
                            }
                            setRunning(false);
                        }
                    }

                    JGCClientEndPointInfo::~JGCClientEndPointInfo(){
                        delete objects;
                    }
                }
            }
        }
    }
}



