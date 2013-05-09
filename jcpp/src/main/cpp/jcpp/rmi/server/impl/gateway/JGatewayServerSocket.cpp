#include "JGatewayServerSocket.h"
#include "JGatewaySocket.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayServerSocketClass : public JClass{
                      public:
                        JGatewayServerSocketClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.GatewayServerSocket";
                            this->name="jcpp.rmi.server.impl.gateway.GatewayServerSocket";
                            this->simpleName="GatewayServerSocket";
                        }

                        JClass* getSuperclass(){
                            return JServerSocket::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayServerSocket::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayServerSocketClass();
                        }
                        return clazz;
                    }

                    JGatewayServerSocket::JGatewayServerSocket(JString* host, JPrimitiveInt* port,JGatewayConfiguration* gatewayConfiguration):JServerSocket(host,port,new JPrimitiveInt(gatewayConfiguration->getBackLog()->get()),getClazz()){
                        this->gatewayConfiguration=gatewayConfiguration;
                    }

                    JSocket* JGatewayServerSocket::accept(){
                        JSocket* socket=JServerSocket::accept();
                        socket->setReceiveBufferSize(gatewayConfiguration->getReceiveBufferSize()->get());
                        socket->setSendBufferSize(gatewayConfiguration->getSendBufferSize()->get());
                        socket->setSoTimeout(gatewayConfiguration->getReadTimeout()->get());
                        return new JGatewaySocket(socket,socket->getInputStream(),gatewayConfiguration);//TODO handle HTTP
                    }

                    JString JGatewayServerSocket::toString(){
                        return "GatewayServerSocket[ServerSocket:" + JServerSocket::toString() + "]";
                    }

                    JGatewayServerSocket::~JGatewayServerSocket(){
                    }
                }
            }
        }
    }
}


