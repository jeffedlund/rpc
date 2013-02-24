#include "JGCClientEndPointInfo.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
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

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGCClientEndPointInfo::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGCClientEndPointInfoClass();
                        }
                        return clazz;
                    }

                    JGCClientEndPointInfo::JGCClientEndPointInfo(JEndPoint* remoteEndPoint){
                        this->remoteEndPoint = remoteEndPoint;
                        this->objects = new map<JString*, JObject*>();
                        //TODO this->gc = localServer->lookup(remoteEndPoint, JIGC::getClazz());
                        this->isRunning = false;
                        this->connections = NULL;//TODO localServer->getObjectInformations()->getTransport()->getConnections(remoteEndPoint);
                    }

                    void JGCClientEndPointInfo::doExport(JString* id, JObject* object){
                        if (objects->size() == 0) {
                            scheduledFuture = NULL;//TODO localServer->getScheduledExecutorService()->schedule(this, localServer->getConnectionConfiguration()->getGcClientTimeout(),localServer->getConnectionConfiguration()->getGcClientTimeout());
                        }
                        objects->insert(pair<JString*,JObject*>(id, object));
                    }

                    void JGCClientEndPointInfo::unexport(JString* id){
                        objects->erase(id);
                        if (objects->size() == 0) {
                            unexport();
                        }
                    }

                    bool JGCClientEndPointInfo::ping(){
                        throwable = NULL;
/*                        String[] idsArray = objects.keySet().toArray(new String[0]);
                        boolean[] ping = null;
                        long t1 = 0;
                        try {
                            t1 = System.currentTimeMillis();
                            connections.setInvocationTimeLimit();
                            ping = gc.ping(localServer.getEndPoint(), idsArray);
                        } catch (Throwable e) {
                            throwable = e;
                            if (++gcExceptionCount >= localServer.getConnectionConfiguration().getGcClientExceptionThreshold()) {
                                unexport();
                                return false;
                            }
                            return true;
                        } finally {
                            connections.removeInvocationTimeLimit();
                        }
                        gcExceptionCount = 0;
                        for (int i = 0; i < ping.length; i++) {
                            if (!ping[i]) {
                                unexport(idsArray[i]);
                            }
                        }
                        if (objects.size() == 0) {
                            return false;
                        }*/
                        return true;
                    }

                    void JGCClientEndPointInfo::unexport(){
                        lock();
                        //TODO endPointInfos->erase(remoteEndPoint);
                        if (future != NULL) {
                            future->cancel();
                        }
                        scheduledFuture->cancel();
                        delete scheduledFuture;
                        unlock();
                    }

                    void JGCClientEndPointInfo::run(){
                        if (!isRunning) {//TODO
                            /*future = localServer.getExecutorService().submit(new Callable<Void>() {
                                        public Void call() {
                                            String oldName = Thread.currentThread().getName();
                                            try {
                                                isRunning.set(true);
                                                boolean ping = ping();
                                                Object[] values = null;
                                                synchronized (EndPointInfo.this) {
                                                    values = objects.values().toArray(new Object[0]);
                                                }
                                                if (!ping) {
                                                    if (gcExceptionCount == 0) {
                                                        gcClientListener.objectDead(remoteEndPoint, values);
                                                    } else {
                                                        gcClientListener.objectDead(remoteEndPoint, values, throwable);
                                                    }
                                                } else {
                                                    if (gcExceptionCount == 0) {
                                                        gcClientListener.objectAlive(remoteEndPoint, values);
                                                    } else {
                                                        gcClientListener.objectMaybeDead(remoteEndPoint, values, throwable);
                                                    }
                                                }
                                            } finally {
                                                isRunning.set(false);
                                            }
                                        }
                                    });*/
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



