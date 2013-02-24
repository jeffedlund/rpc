#include "JGC.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    JObject* invokePing(JObject* object,vector<JObject*>*args){
                        JGC* gc=(JGC*)object;
                        return gc->ping((JEndPoint*)args->at(0),(JPrimitiveArray*)args->at(1));
                    }

                    JObject* invokeEndPointDead(JObject* object,vector<JObject*>*args){
                        JGC* gc=(JGC*)object;
                        gc->endPointDead((JEndPoint*)args->at(0));
                        return NULL;
                    }

                    JObject* invokeGetExportedEndPoints(JObject* object,vector<JObject*>*args){
                        JGC* gc=(JGC*)object;
                        return gc->getExportedEndPoints();
                    }

                    class JGCClass : public JClass{
                      public:
                        JGCClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.GC";
                            this->name="jcpp.rmi.server.impl.connection.GC";
                            this->simpleName="GC";
                            addInterface(JIGC::getClazz());
                            vector<JClass*>* param=new vector<JClass*>();
                            param->push_back(JEndPoint::getClazz());
                            param->push_back(JPrimitiveArray::getClazz(JString::getClazz()));
                            addMethod(new JMethod("ping",this,JPrimitiveArray::getClazz(JBoolean::getClazz()),param,invokePing));

                            param=new vector<JClass*>();
                            param->push_back(JEndPoint::getClazz());
                            addMethod(new JMethod("endPointDead",this,JVoid::getClazz(),param,invokeEndPointDead));

                            param=new vector<JClass*>();
                            addMethod(new JMethod("getExportedEndPoints",this,JPrimitiveArray::getClazz(JEndPoint::getClazz()),param,invokeGetExportedEndPoints));
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGC::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGCClass();
                        }
                        return clazz;
                    }

                    JGC::JGC(JExecutorService* executorService, JScheduledExecutorService* scheduledExecutorService, JConnectionConfiguration* connectionConfiguration):JObject(getClazz()){
                        this->endPointInfos = new map<JEndPoint*, JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>();
                        this->executorService = executorService;
                        this->scheduledExecutorService = scheduledExecutorService;
                        this->connectionConfiguration = connectionConfiguration;
                    }

                    JPrimitiveArray* JGC::getExportedEndPoints(){
                        JPrimitiveArray* ar;
                        lock();
                        ar=new JPrimitiveArray(JEndPoint::getClazz(),endPointInfos->size());
                        int i=0;
                        map<JEndPoint*,JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>::iterator it=endPointInfos->begin();
                        for (;it!=endPointInfos->end();it++){
                            ar->set(i,(*it).first);
                            i++;
                        }
                        unlock();
                        return ar;
                    }

                    JScheduledExecutorService* JGC::getScheduledExecutorService(){
                        return scheduledExecutorService;
                    }

                    JConnectionConfiguration* JGC::getConnectionConfiguration(){
                        return connectionConfiguration;
                    }

                    JPrimitiveArray* JGC::ping(JEndPoint* endPoint, JPrimitiveArray* ids){
                        JPrimitiveArray* returnPing=new JPrimitiveArray(JBoolean::getClazz(),ids->size());
                        lock();
                        JGCEndPointInfo* endPointInfo = getFromMap(endPointInfos,endPoint);
                        unlock();
                        if (endPointInfo != NULL) {
                            endPointInfo->ping(returnPing, ids);
                        }
                        return returnPing;
                    }

                    void JGC::doExport(vector<JObjectInformation*>* objInfoSet, JEndPoint* endPoint){
                        lock();
                        for (unsigned int i=0;i<objInfoSet->size();i++){
                            JObjectInformation* objInfo=objInfoSet->at(i);
                            doExport(objInfo, endPoint);
                        }
                        unlock();
                    }

                    void JGC::unexport(JEndPoint* endPoint){
                        JGCEndPointInfo* endPointInfo;
                        lock();
                        endPointInfo = getFromMap(endPointInfos,endPoint);
                        unlock();
                        if (endPointInfo != NULL) {
                            endPointInfo->unexport();
                        }
                    }

                    void JGC::unexport(){
                        map<JEndPoint*,JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>* infos;
                        lock();
                        infos = new map<JEndPoint*,JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>(*endPointInfos);
                        unlock();
                        map<JEndPoint*,JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>::iterator it=infos->begin();
                        for (;it!=infos->end();it++){
                            (*it).second->unexport();
                        }
                    }

                    void JGC::endPointDead(JEndPoint* endPoint){
                        unexport(endPoint);
                    }

                    void JGC::doExport(JObjectInformation* objInfo, JEndPoint* endPoint){
                        lock();
                        JGCEndPointInfo* endPointInfo = getFromMap(endPointInfos,endPoint);
                        unlock();
                        if (endPointInfo == NULL) {
                            endPointInfo = new JGCEndPointInfo(this,endPoint);
                            lock();
                            endPointInfos->insert(pair<JEndPoint*,JGCEndPointInfo*>(endPoint, endPointInfo));
                            unlock();
                        }
                        endPointInfo->doExport(objInfo);
                    }

                    void JGC::remove(JEndPoint* e){
                        lock();
                        endPointInfos->erase(e);
                        unlock();
                    }

                    JGC::~JGC(){
                        delete endPointInfos;
                    }
                }
            }
        }
    }
}

