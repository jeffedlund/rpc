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
                            return JInputStream::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayCompressionInputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayCompressionInputStreamClass();
                        }
                        return clazz;
                    }

                    JGatewayCompressionInputStream::JGatewayCompressionInputStream(JInputStream* in,JGatewayConfiguration* gatewayConfiguration):JInputStream(getClazz()){
                        this->gatewayInputStream=new JGatewayInputStream(in);
                    }

                    JRoute* JGatewayCompressionInputStream::getRoute(){
                        return gatewayInputStream->getRoute();
                    }

                    jlong JGatewayCompressionInputStream::available(){
                        return gatewayInputStream->available();
                    }

                    bool JGatewayCompressionInputStream::waitForReadyRead(int w){
                        return gatewayInputStream->waitForReadyRead(w);
                    }

                    jint JGatewayCompressionInputStream::read(){
                        return gatewayInputStream->read();
                    }

                    jint JGatewayCompressionInputStream::read(jbyte b[], int off, int len){
                        return gatewayInputStream->read(b,off,len);
                    }

                    jbyte JGatewayCompressionInputStream::peekByte(){
                        return gatewayInputStream->peekByte();
                    }

                    jbyte JGatewayCompressionInputStream::readByte(){
                        return gatewayInputStream->readByte();
                    }

                    jshort JGatewayCompressionInputStream::readShort(){
                        return gatewayInputStream->readShort();
                    }

                    jushort JGatewayCompressionInputStream::readUnsignedShort(){
                        return gatewayInputStream->readUnsignedShort();
                    }

                    jint JGatewayCompressionInputStream::readInt(){
                        return gatewayInputStream->readInt();
                    }

                    jlong JGatewayCompressionInputStream::readLong(){
                        return gatewayInputStream->readLong();
                    }

                    float JGatewayCompressionInputStream::readFloat(){
                        return gatewayInputStream->readFloat();
                    }

                    double JGatewayCompressionInputStream::readDouble(){
                        return gatewayInputStream->readDouble();
                    }

                    char JGatewayCompressionInputStream::readChar(){
                        return gatewayInputStream->readChar();
                    }

                    bool JGatewayCompressionInputStream::readBool(){
                        return gatewayInputStream->readBool();
                    }

                    void JGatewayCompressionInputStream::close(){
                        gatewayInputStream->close();
                    }

                    JGatewayCompressionInputStream::~JGatewayCompressionInputStream(){
                        delete gatewayInputStream;
                    }
                }
            }
        }
    }
}


