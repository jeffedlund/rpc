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
                            return JOutputStream::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayCompressionOutputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayCompressionOutputStreamClass();
                        }
                        return clazz;
                    }

                    JGatewayCompressionOutputStream::JGatewayCompressionOutputStream(JOutputStream* out,JRoute* route):JOutputStream(getClazz()){
                        this->gatewayOutputStream=new JGatewayOutputStream(out,route);
                    }

                    JRoute* JGatewayCompressionOutputStream::getRoute(){
                        return gatewayOutputStream->getRoute();
                    }

                    void JGatewayCompressionOutputStream::write(jint b){
                        gatewayOutputStream->write(b);
                    }

                    void JGatewayCompressionOutputStream::write(jbyte b[]){
                        gatewayOutputStream->write(b);

                    }

                    void JGatewayCompressionOutputStream::write(jbyte b[], int off, int len){
                        gatewayOutputStream->write(b,off,len);
                    }

                    void JGatewayCompressionOutputStream::flush(){
                        gatewayOutputStream->flush();
                    }

                    void JGatewayCompressionOutputStream::close(){
                        gatewayOutputStream->close();
                    }

                    void JGatewayCompressionOutputStream::writeBoolean(bool v){
                        gatewayOutputStream->writeBoolean(v);
                    }

                    void JGatewayCompressionOutputStream::writeByte(jbyte v){
                        gatewayOutputStream->writeByte(v);
                    }

                    void JGatewayCompressionOutputStream::writeShort(jshort v){
                        gatewayOutputStream->writeShort(v);
                    }

                    void JGatewayCompressionOutputStream::writeChar(jushort v){
                        gatewayOutputStream->writeChar(v);
                    }

                    void JGatewayCompressionOutputStream::writeInt(jint v){
                        gatewayOutputStream->writeInt(v);
                    }

                    void JGatewayCompressionOutputStream::writeLong(jlong v){
                        gatewayOutputStream->writeLong(v);
                    }

                    void JGatewayCompressionOutputStream::writeFloat(float v){
                        gatewayOutputStream->writeFloat(v);
                    }

                    void JGatewayCompressionOutputStream::writeDouble(double v){
                        gatewayOutputStream->writeDouble(v);
                    }

                    JGatewayCompressionOutputStream::~JGatewayCompressionOutputStream(){
                        delete gatewayOutputStream;
                    }
                }
            }
        }
    }
}



