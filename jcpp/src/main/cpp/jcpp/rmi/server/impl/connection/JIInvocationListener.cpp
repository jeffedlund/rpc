#include "JIInvocationListener.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIInvocationListenerClass : public JClass{
                      public:
                        JIInvocationListenerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IInvocationListener";
                            this->name="jcpp.rmi.server.impl.connection.IInvocationListener";
                            this->simpleName="IInvocationListener";
                            this->bIsInterface=true;
                        }

                        JClass* getSuperclass(){
                            return JInterface::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JIInvocationListener::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIInvocationListenerClass();
                        }
                        return clazz;
                    }

                    JIInvocationListener::~JIInvocationListener(){
                    }
                }
            }
        }
    }
}
