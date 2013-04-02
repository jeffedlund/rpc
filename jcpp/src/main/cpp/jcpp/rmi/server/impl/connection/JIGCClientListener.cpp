#include "JIGCClientListener.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIGCClientListenerClass : public JClass{
                      public:
                        JIGCClientListenerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IGCClientListener";
                            this->name="jcpp.rmi.server.impl.connection.IGCClientListener";
                            this->simpleName="IGCClientListener";
                            this->bIsInterface=true;
                        }

                        JClass* getSuperclass(){
                            return JInterface::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JIGCClientListener::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGCClientListenerClass();
                        }
                        return clazz;
                    }

                    JIGCClientListener::~JIGCClientListener(){
                    }
                }
            }
        }
    }
}

