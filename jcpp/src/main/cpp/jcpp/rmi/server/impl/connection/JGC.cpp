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
                            addInterface(JIGC::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
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
                        jint i=0;
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
                        JPrimitiveArray* returnPing=new JPrimitiveArray(JPrimitiveBoolean::getClazz(),ids->size());
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

