#ifndef JGATEWAYCONFIGURATION_H
#define JGATEWAYCONFIGURATION_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveBoolean.h"
#include "JArrayList.h"
#include "JString.h"
#include "Object.h"
#include "JAddress.h"
#include "JSocket.h"
#include "JRoute.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JCPP_LIBRARY_EXPORT JGatewayConfiguration : public JObject, JSerializable{
                        protected:
                            JInteger* backLog;
                            JInteger* receiveBufferSize;
                            JInteger* sendBufferSize;
                            JInteger* readTimeout;
                            JInteger* connectionTimeout;

                        public:
                            static const jint BACKLOG = 400;
                            static const jint RECEIVE_BUFFER_SIZE = 20480;
                            static const jint SEND_BUFFER_SIZE = 20480;
                            static const jint READ_TIMEOUT = 24 * 3600 * 1000; // 24 hours
                            static const jint CONNECTION_TIME_OUT = 60000;

                            JGatewayConfiguration(JInteger* backLog, JInteger* receiveBufferSize, JInteger* sendBufferSize, JInteger* readTimeout, JInteger* connectionTimeout);
                            JGatewayConfiguration();
                            static JClass* getClazz();

                            JInteger* getBackLog();
                            JInteger* getReceiveBufferSize();
                            JInteger* getSendBufferSize();
                            JInteger* getReadTimeout();
                            JInteger* getConnectionTimeout();
                            void setBackLog(JInteger* backLog);
                            void setReceiveBufferSize(JInteger* receiveBufferSize);
                            void setSendBufferSize(JInteger* sendBufferSize);
                            void setReadTimeout(JInteger* readTimeout);
                            void setConnectionTimeout(JInteger* connectionTimeout);
                            virtual ~JGatewayConfiguration();
                        };
                }
            }
        }
    }
}

#endif // JGATEWAYCONFIGURATION_H
