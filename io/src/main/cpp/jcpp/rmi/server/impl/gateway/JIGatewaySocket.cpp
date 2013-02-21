#include "JIGatewaySocket.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JIGatewaySocketClass : public JClass{
                      public:
                        JIGatewaySocketClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.IGatewaySocket";
                            this->name="jcpp.rmi.server.impl.gateway.IGatewaySocket";
                            this->simpleName="IGatewaySocket";
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

                    JClass* JIGatewaySocket::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGatewaySocketClass();
                        }
                        return clazz;
                    }
                }
            }
        }
    }
}



