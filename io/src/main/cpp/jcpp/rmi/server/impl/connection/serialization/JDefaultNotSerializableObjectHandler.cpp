#include "JDefaultNotSerializableObjectHandler.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JNotSerializableException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    namespace serialization{
                        class JDefaultNotSerializableObjectHandlerClass : public JClass{
                          public:
                            JDefaultNotSerializableObjectHandlerClass(){
                                this->canonicalName="jcpp.rmi.server.impl.connection.serialization.DefaultNotSerializableObjectHandler";
                                this->name="jcpp.rmi.server.impl.connection.serialization.DefaultNotSerializableObjectHandler";
                                this->simpleName="DefaultNotSerializableObjectHandler";
                                addInterface(JINotSerializableObjectHandler::getClazz());
                            }

                            JClass* getSuperclass(){
                                return JObject::getClazz();
                            }

                            JObject* newInstance(){
                                throw new JDefaultNotSerializableObjectHandler();
                            }
                        };

                        static JClass* clazz;

                        JClass* JDefaultNotSerializableObjectHandler::getClazz(){
                            if (clazz==NULL){
                                clazz=new JDefaultNotSerializableObjectHandlerClass();
                            }
                            return clazz;
                        }

                        JDefaultNotSerializableObjectHandler::JDefaultNotSerializableObjectHandler():JObject(getClazz()){
                        }

                        JObject* JDefaultNotSerializableObjectHandler::handleNotSerializableObject(JObject* obj){
                            return new JNotSerializableException("Cannot serialize the object of type: " + obj->getClass()->getName() + ". Object: " + obj->toString());
                        }
                    }
                }
            }
        }
    }
}

