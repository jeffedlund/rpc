#ifndef JTRANSPORTCONFIGURATION_H
#define JTRANSPORTCONFIGURATION_H

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
#include "JGatewayConfiguration.h"
#include "JCPP.h"
#include "JLong.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JCPP_LIBRARY_EXPORT JTransportConfiguration : public JObject, public JSerializable{
                        protected:
                            JGatewayConfiguration* gatewayConfiguration;
                            JLong* connectionPoolTimeout;
                            JInteger* socketTimeout;
                            JInteger* pingTimeout;
                            JInteger* limitedSocketTimeout;
                            JLong* timeoutTimerInterval;

                        public:
                            JTransportConfiguration();
                            JTransportConfiguration(JGatewayConfiguration* gatewayConfiguration, JLong* connectionTimeout, JInteger* socketTimeout, JInteger* pingTimeout, JInteger* limitedSocketTimeout, JLong* timeoutTimerInterval);

                            static JClass* getClazz();
                            static const jbyte MSG_TYPE_PING = (jbyte) 0x11;
                            static const jbyte MSG_TYPE_CALL = (jbyte) 0x21;
                            static const jbyte MSG_TYPE_OK = (jbyte) 0x31;
                            static const jbyte MSG_TYPE_EXCEPTION = (jbyte) 0x41;
                            static const jint MAGIC_NUMBER = 1234;
                            static const jlong DEFAULT_CONNECTION_POOL_TIMEOUT = 60000 * 10;
                            static const jint DEFAULT_SOCKET_TIMEOUT = 24 * 3600 * 1000; // 24 hours
                            static const jint DEFAULT_PING_TIMEOUT = 30000;
                            static const jint LIMITED_SOCKET_TIMEOUT = 60000 * 3;
                            static const jlong TIMEOUT_TIMER_INTERVAL = 60000 * 5;

                            JGatewayConfiguration* getGatewayConfiguration();
                            void setGatewayConfiguration(JGatewayConfiguration* gatewayConfiguration);
                            JLong* getConnectionPoolTimeout();
                            void setConnectionPoolTimeout(JLong* connectionTimeout);
                            JInteger* getSocketTimeout();
                            void setSocketTimeout(JInteger* socketTimeout);
                            JInteger* getLimitedSocketTimeout();
                            void setLimitedSocketTimeout(JInteger* limitedSocketTimeout);
                            JInteger* getPingTimeout();
                            void setPingTimeout(JInteger* pingTimeout);
                            JLong* getTimeoutTimerInterval();
                            void setTimeoutTimerInterval(JLong* timeoutTimerInterval);
                            virtual ~JTransportConfiguration();
                    };
                }
            }
        }
    }
}

#endif // JTRANSPORTCONFIGURATION_H
