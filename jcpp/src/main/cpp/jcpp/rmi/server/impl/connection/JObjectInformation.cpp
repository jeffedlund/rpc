#include "JObjectInformation.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
#include "JObjectHandler.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JObjectInformationClass : public JClass{
                      public:
                        JObjectInformationClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ObjectInformation";
                            this->name="jcpp.rmi.server.impl.connection.ObjectInformation";
                            this->simpleName="ObjectInformation";
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JObjectInformation::getClazz(){
                        if (clazz==NULL){
                            clazz=new JObjectInformationClass();
                        }
                        return clazz;
                    }

                    JObjectInformation::JObjectInformation(JString* id, JObject* object, vector<JClass*>* interfaces, JObjectInformations* objectInformations, JILifecycle* lifecycle, JGC*){
                        this->object = object;
                        this->id = id;
                        this->objectInformations = objectInformations;
                        this->objectHandler = new JObjectHandler(objectInformations, interfaces, new JObjectPointer(objectInformations->getTransport()->getLocalEndPoint(), id));
                        this->lifecycle = lifecycle;
                        this->exportedEndPoints = new map<JEndPoint*, JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>();
                    }

                    JObject* JObjectInformation::getObject(){
                        return object;
                    }

                    JString* JObjectInformation::getId(){
                        return id;
                    }

                    JILifecycle* JObjectInformation::getLifecycle(){
                        return lifecycle;
                    }

                    JObjectHandler* JObjectInformation::getObjectHandler(){
                        return objectHandler;
                    }

                    void JObjectInformation::exported(){
                        lifecycle->doExport(this);
                    }

                    void JObjectInformation::doExport(JGCEndPointInfo* remoteEndPointInfo){
                        lock();
                        exportedEndPoints->insert(pair<JEndPoint*,JGCEndPointInfo*>(remoteEndPointInfo->getRemoteEndPoint(),remoteEndPointInfo));
                        unlock();
                        lifecycle->doExport(this,remoteEndPointInfo->getRemoteEndPoint());
                    }

                    void JObjectInformation::unexport(JEndPoint* endPoint){
                        lock();
                        exportedEndPoints->erase(endPoint);
                        unlock();
                        lifecycle->unexport(this,endPoint);
                    }

                    void JObjectInformation::unexport(){
                        objectInformations->remove(id);
                        map<JEndPoint*,JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>* endPointInfos;
                        lock();
                        endPointInfos=new map<JEndPoint*,JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>(*exportedEndPoints);
                        exportedEndPoints->clear();
                        unlock();
                        map<JEndPoint*,JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>::iterator it=endPointInfos->begin();
                        for (;it!=endPointInfos->end();it++){
                            (*it).second->unexport(this);
                            lifecycle->unexport(this,(*it).second->getRemoteEndPoint());
                        }
                        delete endPointInfos;
                        lifecycle->unexport(this);
                    }

                    string JObjectInformation::toString(){
                        return "ObjectInformation[Id[" + id->toString() + "], Object[" + object->toString() + "]]";
                    }

                    JObjectInformation::~JObjectInformation(){
                        delete objectHandler;
                        delete exportedEndPoints;
                    }
                }
            }
        }
    }
}


