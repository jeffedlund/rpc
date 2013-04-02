#include "JGatewayCompressionInputStream.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayCompressionInputStreamClass : public JClass{
                      public:
                        JGatewayCompressionInputStreamClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.GatewayCompressionInputStream";
                            this->name="jcpp.rmi.server.impl.gateway.GatewayCompressionInputStream";
                            this->simpleName="GatewayCompressionInputStream";
                        }

                        JClass* getSuperclass(){
                            return JFilterInputStream::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayCompressionInputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayCompressionInputStreamClass();
                        }
                        return clazz;
                    }

                    JGatewayCompressionInputStream::JGatewayCompressionInputStream(JInputStream* in,JGatewayConfiguration*):JFilterInputStream(in,getClazz()){
                        this->gatewayInputStream=new JGatewayInputStream(in);
                    }

                    JRoute* JGatewayCompressionInputStream::getRoute(){
                        return gatewayInputStream->getRoute();
                    }

                    JGatewayCompressionInputStream::~JGatewayCompressionInputStream(){
                        delete gatewayInputStream;
                    }
                }
            }
        }
    }
}


