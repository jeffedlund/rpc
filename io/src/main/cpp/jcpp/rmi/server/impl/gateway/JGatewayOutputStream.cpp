#include "JGatewayOutputStream.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{

                    class JGatewayOutputStreamClass : public JClass{
                      public:
                        JGatewayOutputStreamClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.JGatewayOutputStream";
                            this->name="jcpp.rmi.server.impl.gateway.JGatewayOutputStream";
                            this->simpleName="JGatewayOutputStream";
                        }

                        JClass* getSuperclass(){
                            return JObjectOutputStream::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayOutputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayOutputStreamClass();
                        }
                        return clazz;
                    }

                    JGatewayOutputStream::JGatewayOutputStream(JOutputStream* out,JRoute* route):JObjectOutputStream(out){
                        this->route=route;
                        writeObject(route);
                        flush();
                    }

                    JRoute* JGatewayOutputStream::getRoute(){
                        return route;
                    }

                    JGatewayOutputStream::~JGatewayOutputStream(){
                        delete route;
                    }
                }
            }
        }
    }
}

