#include "JGatewayInputStream.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{

                    class JGatewayInputStreamClass : public JClass{
                      public:
                        JGatewayInputStreamClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.JGatewayInputStream";
                            this->name="jcpp.rmi.server.impl.gateway.JGatewayInputStream";
                            this->simpleName="JGatewayInputStream";
                        }

                        JClass* getSuperclass(){
                            return JObjectInputStream::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayInputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayInputStreamClass();
                        }
                        return clazz;
                    }

                    JGatewayInputStream::JGatewayInputStream(JInputStream* in):JObjectInputStream(in){
                        route=(JRoute*)readObject();
                    }

                    JRoute* JGatewayInputStream::getRoute(){
                        return route;
                    }

                    JGatewayInputStream::~JGatewayInputStream(){
                        delete route;
                    }
                }
            }
        }
    }
}
