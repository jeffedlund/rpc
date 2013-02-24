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
                    class JGCClass : public JClass{
                      public:
                        JGCClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.GC";
                            this->name="jcpp.rmi.server.impl.connection.GC";
                            this->simpleName="GC";
                            addInterface(JIGC::getClazz());//TODO addMethod
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
                        this->endPointInfos = new map<JEndPoint*, JGCEndPointInfo*>();//TODO use less
                        this->executorService = executorService;
                        this->scheduledExecutorService = scheduledExecutorService;
                        this->connectionConfiguration = connectionConfiguration;
                    }

                    JPrimitiveArray* JGC::getExportedEndPoints(){
                        return NULL;//TODO fetch from endpointinfos.key
                    }

                    JPrimitiveArray* JGC::ping(JEndPoint* endPoint, JPrimitiveArray* ids){
                        JPrimitiveArray* returnPing=new JPrimitiveArray(JBoolean::getClazz(),ids->size());
                        JGCEndPointInfo* endPointInfo = getFromMap(endPointInfos,endPoint);
                        if (endPointInfo != NULL) {
                            endPointInfo->ping(returnPing, ids);
                        }
                        return returnPing;
                    }

                    void JGC::doExport(vector<JObjectInformation*>* objInfoSet, JEndPoint* endPoint){
                        for (unsigned int i=0;i<objInfoSet->size();i++){
                            JObjectInformation* objInfo=objInfoSet->at(i);
                            doExport(objInfo, endPoint);
                        }
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
                        map<JEndPoint*,JGCEndPointInfo*>* infos;
                        lock();
                        infos = new map<JEndPoint*,JGCEndPointInfo*>(*endPointInfos);
                        unlock();
                        map<JEndPoint*,JGCEndPointInfo*>::iterator it=infos->begin();
                        for (;it!=infos->end();it++){
                            (*it).second->unexport();
                        }
                    }

                    void JGC::endPointDead(JEndPoint* endPoint){
                        unexport(endPoint);
                    }

                    void JGC::doExport(JObjectInformation* objInfo, JEndPoint* endPoint){
                        JGCEndPointInfo* endPointInfo = getFromMap(endPointInfos,endPoint);
                        if (endPointInfo == NULL) {
                            endPointInfo = new JGCEndPointInfo(endPoint);
                            endPointInfos->insert(pair<JEndPoint*,JGCEndPointInfo*>(endPoint, endPointInfo));
                        }
                        endPointInfo->doExport(objInfo);
                    }

                    JGC::~JGC(){
                        delete endPointInfos;
                    }
                }
            }
        }
    }
}

