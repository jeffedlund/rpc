#include "JIGCClient.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIGCClientClass : public JClass{
                      public:
                        JIGCClientClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IGCClient";
                            this->name="jcpp.rmi.server.impl.connection.IGCClient";
                            this->simpleName="IGCClient";
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

                    JClass* JIGCClient::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGCClientClass();
                        }
                        return clazz;
                    }

                    JIGCClient::~JIGCClient(){
                    }
                }
            }
        }
    }
}
