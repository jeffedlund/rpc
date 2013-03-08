#include "JIInvocationExceptionHandler.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIInvocationExceptionHandlerClass : public JClass{
                      public:
                        JIInvocationExceptionHandlerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IInvocationExceptionHandler";
                            this->name="jcpp.rmi.server.impl.connection.IInvocationExceptionHandler";
                            this->simpleName="IInvocationExceptionHandler";
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

                    JClass* JIInvocationExceptionHandler::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIInvocationExceptionHandlerClass();
                        }
                        return clazz;
                    }

                    JIInvocationExceptionHandler::~JIInvocationExceptionHandler(){
                    }
                }
            }
        }
    }
}

