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
                            this->canonicalName="jcpp.rmi.server.impl.connection.GCEndPointInfo";//TODO
                            this->name="jcpp.rmi.server.impl.connection.GCEndPointInfo";
                            this->simpleName="GCEndPointInfo";
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

                    JClass* JGCEndPointInfo::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGCEndPointInfoClass();
                        }
                        return clazz;
                    }

                    JGCEndPointInfo::JGCEndPointInfo(JEndPoint* remoteEndPoint){
                        this->exportedObjects = new map<JString*, JObjectInformation*>();//TODO use less
                        this->remoteEndPoint = remoteEndPoint;
                        this->isRunning = false;
                    }

                    bool JGCEndPointInfo::isUpdated(){
                        return previousPingId != lastPingId;
                    }

                    JEndPoint* JGCEndPointInfo::getRemoteEndPoint(){
                        return remoteEndPoint;
                    }

                    void JGCEndPointInfo::doExport(JObjectInformation* objInfo){
                        if (exportedObjects->size() == 0) {
                            scheduledFuture = NULL;//TODO scheduledExecutorService->schedule(this, connectionConfiguration->getGcTimeout(), connectionConfiguration->getGcTimeout());
                        }
                        if (getFromMap(exportedObjects,objInfo->getId()) == NULL) {
                            exportedObjects->insert(pair<JString*,JObjectInformation*>(objInfo->getId(), objInfo));
                            objInfo->doExport(this);
                        }
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
                        vector<JObjectInformation*>* objInfos=new vector<JObjectInformation*>();
                        lock();
                        map<JString*,JObjectInformation*>::iterator it=exportedObjects->begin();
                        for (;it!=exportedObjects->end();it++){
                            objInfos->push_back((*it).second);
                        }
                        //TODO gc.getendPointInfos.remove(remoteEndPoint);
                        if (future != NULL) {
                            future->cancel();
                            delete future;
                        }
                        scheduledFuture->cancel();
                        delete scheduledFuture;
                        scheduledFuture = NULL;
                        unlock();
                        if (objInfos != NULL) {
                            for (unsigned int i=0;i<objInfos->size();i++){
                                JObjectInformation* objInfo= objInfos->at(i);
                                objInfo->unexport(remoteEndPoint);
                            }
                        }
                    }

                    void JGCEndPointInfo::update(){
                        lock();
                        previousPingId = lastPingId;
                        unlock();
                    }

                    void JGCEndPointInfo::ping(JPrimitiveArray* returnPing, JPrimitiveArray* ids){
                        lock();
                        lastPingId = lastPingId + 1;
                        for (unsigned int i = 0; i < ids->size(); i++) {
                            if (getFromMap(exportedObjects,(JString*)ids->get(i))!=NULL) {
                                returnPing->set(i,new JBoolean(true));
                            }else{
                                returnPing->set(i,new JBoolean(false));
                            }
                        }
                        unlock();
                    }

                    void JGCEndPointInfo::run(){
                        if (!isRunning) {//TODO
/*                            future = executorService.submit(new Callable<Void>() {
                                    @Override
                                    public Void call() {
                                        String oldName = Thread.currentThread().getName();
                                        try {
                                            isRunning.set(true);
                                            if (isUpdated()) {
                                                update();
                                            } else {
                                                unexport();
                                            }
                                        } finally {
                                            Thread.currentThread().setName(oldName);
                                            isRunning.set(false);
                                        }
                                        return null;
                                    }
                                });*/
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


