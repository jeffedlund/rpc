#include "JGCEndPointInfo.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JGCEndPointInfoClass : public JClass{
                      public:
                        JGCEndPointInfoClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.GCEndPointInfo";
                            this->name="jcpp.rmi.server.impl.connection.GCEndPointInfo";
                            this->simpleName="GCEndPointInfo";
                            addInterface(JRunnable::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JGCEndPointInfo::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGCEndPointInfoClass();
                        }
                        return clazz;
                    }

                    JGCEndPointInfo::JGCEndPointInfo(JGC* gc,JEndPoint* remoteEndPoint){
                        this->gc=gc;
                        this->exportedObjects = new map<JString*, JObjectInformation*,JString::POINTER_COMPARATOR>();
                        this->remoteEndPoint = remoteEndPoint;
                        this->bIsRunning = false;
                    }

                    bool JGCEndPointInfo::isUpdated(){
                        lock();
                        bool b=previousPingId != lastPingId;
                        unlock();
                        return b;
                    }

                    JEndPoint* JGCEndPointInfo::getRemoteEndPoint(){
                        return remoteEndPoint;
                    }

                    void JGCEndPointInfo::doExport(JObjectInformation* objInfo){
                        lock();
                        if (exportedObjects->size() == 0) {
                            scheduledFuture = gc->getScheduledExecutorService()->schedule(this, gc->getConnectionConfiguration()->getGcTimeout()->get(), gc->getConnectionConfiguration()->getGcTimeout()->get());
                        }
                        if (getFromMap(exportedObjects,objInfo->getId()) == NULL) {
                            exportedObjects->insert(pair<JString*,JObjectInformation*>(objInfo->getId(), objInfo));
                            objInfo->doExport(this);
                        }
                        unlock();
                    }

                    void JGCEndPointInfo::unexport(JObjectInformation* objInfo){
                        JObjectInformation* removedObjInfo;
                        int size;
                        lock();
                        removedObjInfo=getFromMap(exportedObjects,objInfo->getId());
                        exportedObjects->erase(objInfo->getId());
                        size = exportedObjects->size();
                        unlock();
                        if (removedObjInfo != NULL) {
                            if (size == 0) {
                                unexport();
                            }
                        }
                    }

                    void JGCEndPointInfo::unexport(){
                        lock();
                        vector<JObjectInformation*>* objInfos=getValues(exportedObjects);
                        gc->remove(remoteEndPoint);
                        if (future != NULL) {
                            future->cancel();
                            delete future;
                        }
                        scheduledFuture->cancel();
                        delete scheduledFuture;
                        scheduledFuture = NULL;
                        unlock();
                        for (unsigned int i=0;i<objInfos->size();i++){
                            JObjectInformation* objInfo= objInfos->at(i);
                            objInfo->unexport(remoteEndPoint);
                        }
                        delete objInfos;
                    }

                    void JGCEndPointInfo::update(){
                        lock();
                        previousPingId = lastPingId;
                        unlock();
                    }

                    void JGCEndPointInfo::ping(JPrimitiveArray* returnPing, JPrimitiveArray* ids){
                        lock();
                        lastPingId = lastPingId + 1;
                        for (int i = 0; i < ids->size(); i++) {
                            if (getFromMap(exportedObjects,(JString*)ids->get(i))!=NULL) {
                                returnPing->set(i,new JPrimitiveBoolean(true));
                            }else{
                                returnPing->set(i,new JPrimitiveBoolean(false));
                            }
                        }
                        unlock();
                    }

                    bool JGCEndPointInfo::isRunning(){
                        bool b;
                        lock();
                        b=this->bIsRunning;
                        unlock();
                        return b;
                    }

                    void JGCEndPointInfo::setRunning(bool b){
                        lock();
                        this->bIsRunning=b;
                        unlock();
                    }

                    void JGCEndPointInfo::run(){
                        if (!isRunning()) {//TODO same, put later in a separte runnable/thread
                            setRunning(true);
                            if (isUpdated()) {
                                update();
                            } else {
                                unexport();
                            }
                            setRunning(false);
                        }
                    }

                    JGCEndPointInfo::~JGCEndPointInfo(){
                        delete exportedObjects;
                    }
                }
            }
        }
    }
}


