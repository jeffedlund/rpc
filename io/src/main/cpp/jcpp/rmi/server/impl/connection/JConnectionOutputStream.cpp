#include "JConnectionOutputStream.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JConnectionException.h"
#include "JProxy.h"
#include "JObjectHandler.h"
#include "JINotSerializableObjectHandler.h"
#include "JINotExportedObjectListener.h"
#include "JServer.h"
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::connection::serialization;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JConnectionOutputStreamClass : public JClass{
                      public:
                        JConnectionOutputStreamClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ConnectionOutputStream";
                            this->name="jcpp.rmi.server.impl.connection.ConnectionOutputStream";
                            this->simpleName="ConnectionOutputStream";
                        }

                        JClass* getSuperclass(){
                            return JObjectOutputStream::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnectionOutputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionOutputStreamClass();
                        }
                        return clazz;
                    }

                    JConnectionOutputStream::JConnectionOutputStream(JOutputStream* out, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint):JObjectOutputStream(out,getClazz()){
                        this->enableReplaceObject(true);
                        this->objectInformations = objectInformations;
                        this->remoteEndPoint = remoteEndPoint;
                        this->exportedObjInfos = new vector<JObjectInformation*>();
                    }

                    void JConnectionOutputStream::done(){
                        objectInformations->getGC()->doExport(exportedObjInfos, remoteEndPoint);
                        exportedObjInfos->clear();
                    }

                    JObject* JConnectionOutputStream::replaceObject(JObject* obj){
                        JObjectInformation* objInfo = objectInformations->getObjectInformation(obj);
                        if ((objInfo == NULL) && (obj != NULL) && !(JSerializable::getClazz()->isAssignableFrom(obj->getClass()))) {
                            bool isExported = false;
                            JINotExportedObjectListener* notExportedObjectListener = objectInformations->getServer()->getNotExportedObjectListener();
                            if (notExportedObjectListener != NULL) {
                                isExported = notExportedObjectListener->handleNotExportedObject(obj);
                                if (isExported) {
                                    objInfo = objectInformations->getObjectInformation(obj);
                                }
                            }
                            JINotSerializableObjectHandler* notSerializableObjectHandler = objectInformations->getServer()->getNotSerializableObjectHandler();
                            if (!isExported && (notSerializableObjectHandler != NULL)) {
                                return notSerializableObjectHandler->handleNotSerializableObject(obj);
                            }
                        }
                        if (objInfo != NULL) {
                            exportedObjInfos->push_back(objInfo);
                            JObjectHandler* objectHandler = (JObjectHandler*) objInfo->getObjectHandler()->clone();
                            return objectHandler->getProxy();
                        }
                        return obj;
                    }

                    JConnectionOutputStream::~JConnectionOutputStream(){
                    }
                }
            }
        }
    }
}



