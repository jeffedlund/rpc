#include "JGatewayCompressionOutputStream.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayCompressionOutputStreamClass : public JClass{
                      public:
                        JGatewayCompressionOutputStreamClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.GatewayCompressionOutputStream";
                            this->name="jcpp.rmi.server.impl.gateway.GatewayCompressionOutputStream";
                            this->simpleName="GatewayCompressionOutputStream";
                        }

                        JClass* getSuperclass(){
                            return JFilterOutputStream::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayCompressionOutputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayCompressionOutputStreamClass();
                        }
                        return clazz;
                    }

                    JGatewayCompressionOutputStream::JGatewayCompressionOutputStream(JOutputStream* out,JRoute* route):JFilterOutputStream(out,getClazz()){
                        this->gatewayOutputStream=new JGatewayOutputStream(out,route);
                    }

                    JRoute* JGatewayCompressionOutputStream::getRoute(){
                        return gatewayOutputStream->getRoute();
                    }

                    void JGatewayCompressionOutputStream::close(){
                        gatewayOutputStream->close();
                        out->close();
                    }

                    JGatewayCompressionOutputStream::~JGatewayCompressionOutputStream(){
                        delete gatewayOutputStream;
                    }
                }
            }
        }
    }
}



