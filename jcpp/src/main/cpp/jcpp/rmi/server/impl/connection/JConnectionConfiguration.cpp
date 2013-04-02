#include "JConnectionConfiguration.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    static JObject* staticGetTransportConfiguration(JObject* object){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        return s->getTransportConfiguration();
                    }

                    static void staticSetTransportConfiguration(JObject* object,JObject* value){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        s->setTransportConfiguration((JTransportConfiguration*)value);
                    }

                    static JObject* staticGetGcTimeout(JObject* object){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        return s->getGcTimeout();
                    }

                    static void staticSetGcTimeout(JObject* object,JObject* value){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        s->setGcTimeout((JLong*)value);
                    }

                    static JObject* staticGetGcClientTimeout(JObject* object){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        return s->getGcClientTimeout();
                    }

                    static void staticSetGcClientTimeout(JObject* object,JObject* value){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        s->setGcClientTimeout((JLong*)value);
                    }

                    static JObject* staticGetGcClientExceptionThreshold(JObject* object){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        return s->getGcClientExceptionThreshold();
                    }

                    static void staticSetGcClientExceptionThreshold(JObject* object,JObject* value){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        s->setGcClientExceptionThreshold((JInteger*)value);
                    }

                    static JObject* staticGetExecutorCorePoolSize(JObject* object){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        return s->getExecutorCorePoolSize();
                    }

                    static void staticSetExecutorCorePoolSize(JObject* object,JObject* value){
                        JConnectionConfiguration* s=(JConnectionConfiguration*)object;
                        s->setExecutorCorePoolSize((JInteger*)value);
                    }

                    class JConnectionConfigurationClass : public JClass{
                      public:
                        JConnectionConfigurationClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ConnectionConfiguration";
                            this->name="jcpp.rmi.server.impl.connection.ConnectionConfiguration";
                            this->simpleName="ConnectionConfiguration";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("transportConfiguration",JTransportConfiguration::getClazz(),this,staticGetTransportConfiguration,staticSetTransportConfiguration));
                            addField(new JField("gcTimeout",JLong::getClazz(),this,staticGetGcTimeout,staticSetGcTimeout));
                            addField(new JField("gcClientTimeout",JLong::getClazz(),this,staticGetGcClientTimeout,staticSetGcClientTimeout));
                            addField(new JField("gcClientExceptionThreshold",JInteger::getClazz(),this,staticGetGcClientExceptionThreshold,staticSetGcClientExceptionThreshold));
                            addField(new JField("executorCorePoolSize",JInteger::getClazz(),this,staticGetExecutorCorePoolSize,staticSetExecutorCorePoolSize));
                            serialVersionUID=-7733929591819747912ULL;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            return new JConnectionConfiguration();
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnectionConfiguration::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionConfigurationClass();
                        }
                        return clazz;
                    }

                    JConnectionConfiguration::JConnectionConfiguration(){
                        this->transportConfiguration=new JTransportConfiguration();
                        this->gcTimeout=new JLong(GC_TIMEOUT);
                        this->gcClientTimeout=new JLong(GCCLIENT_TIMEOUT);
                        this->gcClientExceptionThreshold=new JInteger(GCCLIENT_EXCEPTION_THRESHOLD);
                        this->executorCorePoolSize=new JInteger(EXECUTOR_CORE_POOL_SIZE);
                    }

                    JConnectionConfiguration::JConnectionConfiguration(JTransportConfiguration* transportConfiguration,JLong* gcTimeout,JLong* gcClientTimeout,JInteger* gcClientExceptionThreshold,JInteger* executorCorePoolSize){
                        this->transportConfiguration=transportConfiguration;
                        this->gcTimeout=gcTimeout;
                        this->gcClientTimeout=gcClientTimeout;
                        this->gcClientExceptionThreshold=gcClientExceptionThreshold;
                        this->executorCorePoolSize=executorCorePoolSize;
                    }

                    JTransportConfiguration* JConnectionConfiguration::getTransportConfiguration(){
                        return transportConfiguration;
                    }

                    void JConnectionConfiguration::setTransportConfiguration(JTransportConfiguration* tc){
                        delete this->transportConfiguration;
                        this->transportConfiguration=tc;
                    }

                    JLong* JConnectionConfiguration::getGcTimeout(){
                        return gcTimeout;
                    }

                    void JConnectionConfiguration::setGcTimeout(JLong* gcTimeout){
                        delete this->gcTimeout;
                        this->gcTimeout=gcTimeout;
                    }

                    JLong* JConnectionConfiguration::getGcClientTimeout(){
                        return gcClientTimeout;
                    }

                    void JConnectionConfiguration::setGcClientTimeout(JLong* gcClientTimeout){
                        delete this->gcClientTimeout;
                        this->gcClientTimeout=gcClientTimeout;
                    }

                    JInteger* JConnectionConfiguration::getGcClientExceptionThreshold(){
                        return gcClientExceptionThreshold;
                    }

                    void JConnectionConfiguration::setGcClientExceptionThreshold(JInteger* t){
                        delete this->gcClientExceptionThreshold;
                        this->gcClientExceptionThreshold=t;
                    }

                    JInteger* JConnectionConfiguration::getExecutorCorePoolSize(){
                        return executorCorePoolSize;
                    }

                    void JConnectionConfiguration::setExecutorCorePoolSize(JInteger* s){
                        delete this->executorCorePoolSize;
                        this->executorCorePoolSize=s;
                    }

                    JConnectionConfiguration::~JConnectionConfiguration(){
                        delete transportConfiguration;
                        delete gcTimeout;
                        delete gcClientTimeout;
                        delete gcClientExceptionThreshold;
                        delete executorCorePoolSize;
                    }
                }
            }
        }
    }
}


