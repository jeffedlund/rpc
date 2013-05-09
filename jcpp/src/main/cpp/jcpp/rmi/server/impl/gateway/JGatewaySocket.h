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
                            bool bSendSocket;
                            JRoute* route;
                            JGatewayConfiguration* gatewayConfiguration;
                            void setSocketSetting();

                        public:
                            JGatewaySocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration);
                            JGatewaySocket(JSocket* socket,JInputStream* in,JGatewayConfiguration* gatewayConfiguration);

                            static JClass* getClazz();

                            JRoute* getRoute();
                            bool isReusable();

                            virtual QObject* getQObject();
                            virtual JInetAddress* getInetAddress();
                            virtual JInetAddress* getLocalAddress();
                            virtual JPrimitiveInt* getPort();
                            virtual JPrimitiveInt* getLocalPort();

                            virtual JInputStream* getInputStream();
                            virtual JOutputStream* getOutputStream();

                            virtual void setTcpNoDelay(bool on);
                            virtual bool getTcpNoDelay();

                            virtual void setSoLinger(bool on, int linger);
                            virtual int getSoLinger();

                            virtual void setOOBInline(bool on);
                            virtual bool getOOBInline();

                            virtual void setSoTimeout(int s);
                            virtual int getSoTimeout();

                            virtual void setSendBufferSize(int size);
                            virtual int getSendBufferSize();

                            virtual void setReceiveBufferSize(int size);
                            virtual int getReceiveBufferSize();

                            virtual void setKeepAlive(bool on);
                            virtual bool getKeepAlive();

                            virtual void setTrafficClass(int tc);
                            virtual int getTrafficClass();

                            virtual void setReuseAddress(bool on);
                            virtual bool getReuseAddress();

                            virtual void close();
                            virtual bool isClosed();


                            JString toString();

                            virtual ~JGatewaySocket();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYSOCKET_H
