#include "JGatewaySocketFactory.h"
#include "JSerializable.h"
#include "JGatewaySocket.h"
#include "JGatewayServerSocket.h"
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewaySocketFactoryClass : public JClass{
                      public:
                        JGatewaySocketFactoryClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.GatewaySocketFactory";
                            this->name="jcpp.rmi.server.impl.gateway.GatewaySocketFactory";
                            this->simpleName="GatewaySocketFactory";
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewaySocketFactory::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewaySocketFactoryClass();
                        }
                        return clazz;
                    }

                    JSocket* JGatewaySocketFactory::createSocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration){
                        if (route!=NULL && route->isHttp()){
                            return NULL;//TODO HttpRequestGatewaySocket
                        }else{
                            return new JGatewaySocket(route,gatewayConfiguration);
                        }
                    }

                    JServerSocket* JGatewaySocketFactory::createServerSocket(JString* host, JPrimitiveInt* port,JGatewayConfiguration* gatewayConfiguration){
                        return new JGatewayServerSocket(host,port,gatewayConfiguration);
                    }

                    JGatewaySocketFactory::~JGatewaySocketFactory(){
                    }
                }
            }
        }
    }
}


