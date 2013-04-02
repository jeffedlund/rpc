#include "JTransportConfiguration.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    static JObject* staticGetGatewayConfiguration(JObject* object){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        return s->getGatewayConfiguration();
                    }

                    static void staticSetGatewayConfiguration(JObject* object,JObject* value){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        s->setGatewayConfiguration((JGatewayConfiguration*)value);
                    }

                    static JObject* staticGetConnectionPoolTimeout(JObject* object){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        return s->getConnectionPoolTimeout();
                    }

                    static void staticSetConnectionPoolTimeout(JObject* object,JObject* value){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        s->setConnectionPoolTimeout((JLong*)value);
                    }

                    static JObject* staticGetSocketTimeout(JObject* object){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        return s->getSocketTimeout();
                    }

                    static void staticSetSocketTimeout(JObject* object,JObject* value){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        s->setSocketTimeout((JInteger*)value);
                    }

                    static JObject* staticGetPingTimeout(JObject* object){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        return s->getPingTimeout();
                    }

                    static void staticSetPingTimeout(JObject* object,JObject* value){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        s->setPingTimeout((JInteger*)value);
                    }

                    static JObject* staticGetLimitedSocketTimeout(JObject* object){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        return s->getLimitedSocketTimeout();
                    }

                    static void staticSetLimitedSocketTimeout(JObject* object,JObject* value){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        s->setLimitedSocketTimeout((JInteger*)value);
                    }

                    static JObject* staticGetTimeoutTimerInterval(JObject* object){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        return s->getTimeoutTimerInterval();
                    }

                    static void staticSetTimeoutTimerInterval(JObject* object,JObject* value){
                        JTransportConfiguration* s=(JTransportConfiguration*)object;
                        s->setTimeoutTimerInterval((JLong*)value);
                    }


                    class JTransportConfigurationClass : public JClass{
                      public:
                        JTransportConfigurationClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.TransportConfiguration";
                            this->name="jcpp.rmi.server.impl.transport.TransportConfiguration";
                            this->simpleName="TransportConfiguration";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("gatewayConfiguration",JGatewayConfiguration::getClazz(),this,staticGetGatewayConfiguration,staticSetGatewayConfiguration));
                            addField(new JField("connectionPoolTimeout",JLong::getClazz(),this,staticGetConnectionPoolTimeout,staticSetConnectionPoolTimeout));
                            addField(new JField("socketTimeout",JInteger::getClazz(),this,staticGetSocketTimeout,staticSetSocketTimeout));
                            addField(new JField("pingTimeout",JInteger::getClazz(),this,staticGetPingTimeout,staticSetPingTimeout));
                            addField(new JField("limitedSocketTimeout",JInteger::getClazz(),this,staticGetLimitedSocketTimeout,staticSetLimitedSocketTimeout));
                            addField(new JField("timeoutTimerInterval",JLong::getClazz(),this,staticGetTimeoutTimerInterval,staticSetTimeoutTimerInterval));
                            serialVersionUID=721031819973449961ULL;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            return new JTransportConfiguration();
                        }
                    };

                    static JClass* clazz;

                    JClass* JTransportConfiguration::getClazz(){
                        if (clazz==NULL){
                            clazz=new JTransportConfigurationClass();
                        }
                        return clazz;
                    }

                    JTransportConfiguration::JTransportConfiguration():JObject(getClazz()){
                        this->gatewayConfiguration=new JGatewayConfiguration();
                        this->connectionPoolTimeout=new JLong(DEFAULT_CONNECTION_POOL_TIMEOUT);
                        this->socketTimeout=new JInteger(DEFAULT_SOCKET_TIMEOUT);
                        this->pingTimeout=new JInteger(DEFAULT_PING_TIMEOUT);
                        this->limitedSocketTimeout=new JInteger(LIMITED_SOCKET_TIMEOUT);
                        this->timeoutTimerInterval=new JLong(TIMEOUT_TIMER_INTERVAL);
                    }

                    JTransportConfiguration::JTransportConfiguration(JGatewayConfiguration* gatewayConfiguration, JLong* connectionTimeout, JInteger* socketTimeout, JInteger* pingTimeout, JInteger* limitedSocketTimeout, JLong* timeoutTimerInterval):JObject(getClazz()){
                        this->gatewayConfiguration=gatewayConfiguration;
                        this->connectionPoolTimeout=connectionTimeout;
                        this->socketTimeout=socketTimeout;
                        this->pingTimeout=pingTimeout;
                        this->limitedSocketTimeout=limitedSocketTimeout;
                        this->timeoutTimerInterval=timeoutTimerInterval;
                    }

                    JGatewayConfiguration* JTransportConfiguration::getGatewayConfiguration(){
                        return gatewayConfiguration;
                    }

                    void JTransportConfiguration::setGatewayConfiguration(JGatewayConfiguration* gatewayConfiguration){
                        this->gatewayConfiguration=gatewayConfiguration;
                    }

                    JLong* JTransportConfiguration::getConnectionPoolTimeout(){
                        return connectionPoolTimeout;
                    }

                    void JTransportConfiguration::setConnectionPoolTimeout(JLong* connectionTimeout){
                        this->connectionPoolTimeout=connectionTimeout;
                    }

                    JInteger* JTransportConfiguration::getSocketTimeout(){
                        return socketTimeout;
                    }

                    void JTransportConfiguration::setSocketTimeout(JInteger* socketTimeout){
                        this->socketTimeout=socketTimeout;
                    }

                    JInteger* JTransportConfiguration::getLimitedSocketTimeout(){
                        return limitedSocketTimeout;
                    }

                    void JTransportConfiguration::setLimitedSocketTimeout(JInteger* limitedSocketTimeout){
                        this->limitedSocketTimeout=limitedSocketTimeout;
                    }

                    JInteger* JTransportConfiguration::getPingTimeout(){
                        return pingTimeout;
                    }

                    void JTransportConfiguration::setPingTimeout(JInteger* pingTimeout){
                        this->pingTimeout=pingTimeout;
                    }

                    JLong* JTransportConfiguration::getTimeoutTimerInterval(){
                        return timeoutTimerInterval;
                    }

                    void JTransportConfiguration::setTimeoutTimerInterval(JLong* timeoutTimerInterval){
                        this->timeoutTimerInterval=timeoutTimerInterval;
                    }

                    JTransportConfiguration::~JTransportConfiguration(){
                        delete this->gatewayConfiguration;
                        delete this->connectionPoolTimeout;
                        delete this->socketTimeout;
                        delete this->pingTimeout;
                        delete this->limitedSocketTimeout;
                        delete this->timeoutTimerInterval;
                    }
                }
            }
        }
    }
}

