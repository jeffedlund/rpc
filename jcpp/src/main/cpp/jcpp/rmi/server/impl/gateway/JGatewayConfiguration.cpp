#include "JGatewayConfiguration.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    static JObject* staticGetBackLog(JObject* object){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        return s->getBackLog();
                    }

                    static void staticSetBackLog(JObject* object,JObject* value){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        s->setBackLog((JInteger*)value);
                    }

                    static JObject* staticGetReceiveBufferSize(JObject* object){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        return s->getReceiveBufferSize();
                    }

                    static void staticSetReceiveBufferSize(JObject* object,JObject* value){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        s->setReceiveBufferSize((JInteger*)value);
                    }

                    static JObject* staticGetSendBufferSize(JObject* object){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        return s->getSendBufferSize();
                    }

                    static void staticSetSendBufferSize(JObject* object,JObject* value){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        s->setSendBufferSize((JInteger*)value);
                    }

                    static JObject* staticGetReadTimeout(JObject* object){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        return s->getReadTimeout();
                    }

                    static void staticSetReadTimeout(JObject* object,JObject* value){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        s->setReadTimeout((JInteger*)value);
                    }

                    static JObject* staticGetConnectionTimeout(JObject* object){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        return s->getConnectionTimeout();
                    }

                    static void staticSetConnectionTimeout(JObject* object,JObject* value){
                        JGatewayConfiguration* s=(JGatewayConfiguration*)object;
                        s->setConnectionTimeout((JInteger*)value);
                    }

                    class JGatewayConfigurationClass : public JClass{
                      public:
                        JGatewayConfigurationClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.GatewayConfiguration";
                            this->name="jcpp.rmi.server.impl.gateway.GatewayConfiguration";
                            this->simpleName="GatewayConfiguration";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("backLog",JInteger::getClazz(),staticGetBackLog,staticSetBackLog));
                            addField(new JField("receiveBufferSize",JInteger::getClazz(),staticGetReceiveBufferSize,staticSetReceiveBufferSize));
                            addField(new JField("sendBufferSize",JInteger::getClazz(),staticGetSendBufferSize,staticSetSendBufferSize));
                            addField(new JField("readTimeout",JInteger::getClazz(),staticGetReadTimeout,staticSetReadTimeout));
                            addField(new JField("connectionTimeout",JInteger::getClazz(),staticGetConnectionTimeout,staticSetConnectionTimeout));
                            serialVersionUID=7816914239055009789ULL;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JGatewayConfiguration();
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewayConfiguration::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewayConfigurationClass();
                        }
                        return clazz;
                    }

                    JGatewayConfiguration::JGatewayConfiguration(JInteger* backLog, JInteger* receiveBufferSize, JInteger* sendBufferSize, JInteger* readTimeout, JInteger* connectionTimeout):JObject(getClazz()){
                        this->backLog=backLog;
                        this->receiveBufferSize=receiveBufferSize;
                        this->sendBufferSize=sendBufferSize;
                        this->readTimeout=readTimeout;
                        this->connectionTimeout=connectionTimeout;
                    }

                    JGatewayConfiguration::JGatewayConfiguration():JObject(getClazz()){
                        backLog=new JInteger(BACKLOG);
                        receiveBufferSize=new JInteger(RECEIVE_BUFFER_SIZE);
                        sendBufferSize=new JInteger(SEND_BUFFER_SIZE);
                        readTimeout=new JInteger(READ_TIMEOUT);
                        connectionTimeout=new JInteger(CONNECTION_TIME_OUT);
                    }

                    JInteger* JGatewayConfiguration::getBackLog(){
                        return backLog;
                    }

                    JInteger* JGatewayConfiguration::getReceiveBufferSize(){
                        return receiveBufferSize;
                    }

                    JInteger* JGatewayConfiguration::getSendBufferSize(){
                        return sendBufferSize;
                    }

                    JInteger* JGatewayConfiguration::getReadTimeout(){
                        return readTimeout;
                    }

                    JInteger* JGatewayConfiguration::getConnectionTimeout(){
                        return connectionTimeout;
                    }

                    void JGatewayConfiguration::setBackLog(JInteger* backLog){
                        delete this->backLog;
                        this->backLog=backLog;
                    }

                    void JGatewayConfiguration::setReceiveBufferSize(JInteger* receiveBufferSize){
                        delete this->receiveBufferSize;
                        this->receiveBufferSize=receiveBufferSize;
                    }

                    void JGatewayConfiguration::setSendBufferSize(JInteger* sendBufferSize){
                        delete this->sendBufferSize;
                        this->sendBufferSize=sendBufferSize;
                    }

                    void JGatewayConfiguration::setReadTimeout(JInteger* readTimeout){
                        delete this->readTimeout;
                        this->readTimeout=readTimeout;
                    }

                    void JGatewayConfiguration::setConnectionTimeout(JInteger* connectionTimeout){
                        delete this->connectionTimeout;
                        this->connectionTimeout=connectionTimeout;
                    }

                    JGatewayConfiguration::~JGatewayConfiguration(){
                        delete backLog;
                        delete receiveBufferSize;
                        delete sendBufferSize;
                        delete readTimeout;
                        delete connectionTimeout;
                    }
                }
            }
        }
    }
}

