#ifndef JGATEWAYSOCKET_H
#define JGATEWAYSOCKET_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JIGatewaySocket.h"
#include "JSocket.h"
#include "JGatewayConfiguration.h"
#include "JGatewayCompressionOutputStream.h"
#include "JGatewayCompressionInputStream.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayCompressionOutputStream;
                    class JGatewayCompressionInputStream;
                    class JCPP_LIBRARY_EXPORT JGatewaySocket : public JSocket, public JIGatewaySocket{
                        protected:
                            JSocket* socket;
                            JInputStream* input;
                            JOutputStream* output;
                            jbool bSendSocket;
                            JRoute* route;
                            JGatewayConfiguration* gatewayConfiguration;
                            void setSocketSetting();

                        public:
                            JGatewaySocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration);
                            JGatewaySocket(JSocket* socket,JInputStream* in,JGatewayConfiguration* gatewayConfiguration);
                            static JClass* getClazz();
                            virtual JRoute* getRoute();
                            virtual jbool isReusable();
                            virtual QObject* getQObject();
                            virtual JInetAddress* getInetAddress();
                            virtual JInetAddress* getLocalAddress();
                            virtual jint getPort();
                            virtual jint getLocalPort();
                            virtual JInputStream* getInputStream();
                            virtual JOutputStream* getOutputStream();
                            virtual void setTcpNoDelay(jbool on);
                            virtual jbool getTcpNoDelay();
                            virtual void setSoLinger(jbool on, jint linger);
                            virtual jint getSoLinger();
                            virtual void setOOBInline(jbool on);
                            virtual jbool getOOBInline();
                            virtual void setSoTimeout(jint s);
                            virtual jint getSoTimeout();
                            virtual void setSendBufferSize(jint size);
                            virtual jint getSendBufferSize();
                            virtual void setReceiveBufferSize(jint size);
                            virtual jint getReceiveBufferSize();
                            virtual void setKeepAlive(jbool on);
                            virtual jbool getKeepAlive();
                            virtual void setTrafficClass(jint tc);
                            virtual jint getTrafficClass();
                            virtual void setReuseAddress(jbool on);
                            virtual jbool getReuseAddress();
                            virtual void close();
                            virtual jbool isClosed();
                            virtual JString toString();
                            virtual ~JGatewaySocket();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYSOCKET_H
