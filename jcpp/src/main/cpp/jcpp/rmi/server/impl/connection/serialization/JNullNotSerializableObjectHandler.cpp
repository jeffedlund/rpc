#include "JNullNotSerializableObjectHandler.h"
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
                        class JNullNotSerializableObjectHandlerClass : public JClass{
                          public:
                            JNullNotSerializableObjectHandlerClass(){
                                this->canonicalName="jcpp.rmi.server.impl.connection.serialization.NullNotSerializableObjectHandler";
                                this->name="jcpp.rmi.server.impl.connection.serialization.NullNotSerializableObjectHandler";
                                this->simpleName="NullNotSerializableObjectHandler";
                                addInterface(JINotSerializableObjectHandler::getClazz());
                            }

                            JClass* getSuperclass(){
                                return JObject::getClazz();
                            }

                            JObject* newInstance(){
                                return new JNullNotSerializableObjectHandler();
                            }
                        };

                        static JClass* clazz;

                        JClass* JNullNotSerializableObjectHandler::getClazz(){
                            if (clazz==NULL){
                                clazz=new JNullNotSerializableObjectHandlerClass();
                            }
                            return clazz;
                        }

                        JNullNotSerializableObjectHandler::JNullNotSerializableObjectHandler():JObject(getClazz()){
                        }

                        JObject* JNullNotSerializableObjectHandler::handleNotSerializableObject(JObject*){
                            return NULL;
                        }

                        JNullNotSerializableObjectHandler::~JNullNotSerializableObjectHandler(){
                        }
                    }
                }
            }
        }
    }
}


