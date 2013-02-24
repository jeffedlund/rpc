#include "JINotSerializableObjectHandler.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    namespace serialization{
                        class JINotSerializableObjectHandlerClass : public JClass{
                          public:
                            JINotSerializableObjectHandlerClass(){
                                this->canonicalName="jcpp.rmi.server.impl.connection.serialization.INotSerializableObjectHandler";
                                this->name="jcpp.rmi.server.impl.connection.serialization.INotSerializableObjectHandler";
                                this->simpleName="INotSerializableObjectHandler";
                                this->bIsInterface=true;
                            }

                            JClass* getSuperclass(){
                                return JInterface::getClazz();
                            }

                            JObject* newInstance(){
                                throw new JInstantiationException("cannot instantiate object of class "+getName());
                            }
                        };

                        static JClass* clazz;

                        JClass* JINotSerializableObjectHandler::getClazz(){
                            if (clazz==NULL){
                                clazz=new JINotSerializableObjectHandlerClass();
                            }
                            return clazz;
                        }
                    }
                }
            }
        }
    }
}