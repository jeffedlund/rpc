#ifndef JCONNECTIONCONFIGURATION_H
#define JCONNECTIONCONFIGURATION_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JAddress.h"
#include "JDataInputStream.h"
#include "JDataOutputStream.h"
#include "JEndPoint.h"
#include "JTransportConfiguration.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JCPP_LIBRARY_EXPORT JConnectionConfiguration : public JObject, public JSerializable{
                        protected:
                            JTransportConfiguration* transportConfiguration;
                            JLong* gcTimeout;
                            JLong* gcClientTimeout;
                            JInteger* gcClientExceptionThreshold;
                            JInteger* executorCorePoolSize;

                        public:
                            JConnectionConfiguration();
                            JConnectionConfiguration(JTransportConfiguration* transportConfiguration,JLong* gcTimeout,JLong* gcClientTimeout,JInteger* gcClientExceptionThreshold,JInteger* executorCorePoolSize);
                            static JClass* getClazz();
                            static const jlong GC_TIMEOUT       = 10 * 60000;
                            static const jlong GCCLIENT_TIMEOUT = 1 * 60000;
                            static const jint GCCLIENT_EXCEPTION_THRESHOLD  = 10;
                            static const jint EXECUTOR_CORE_POOL_SIZE       = 2;
                            virtual JTransportConfiguration* getTransportConfiguration();
                            virtual void setTransportConfiguration(JTransportConfiguration* tc);
                            virtual JLong* getGcTimeout();
                            virtual void setGcTimeout(JLong* gcTimeout);
                            virtual JLong* getGcClientTimeout();
                            virtual void setGcClientTimeout(JLong* gcTimeout);
                            virtual JInteger* getGcClientExceptionThreshold();
                            virtual void setGcClientExceptionThreshold(JInteger* t);
                            virtual JInteger* getExecutorCorePoolSize();
                            virtual void setExecutorCorePoolSize(JInteger* s);
                            virtual ~JConnectionConfiguration();
                    };
                }
            }
        }
    }
}

#endif // JCONNECTIONCONFIGURATION_H
