#ifndef JCONNECTION_H
#define JCONNECTION_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <map>
#include "JSocket.h"
#include "Object.h"
#include "JDataOutputStream.h"
#include "JDataInputStream.h"
#include "JRoute.h"
#include "JConnections.h"
#include "JGatewayConfiguration.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JConnections;
                    class JTransport;
                    class JConnection : public JObject{
                        protected:
                            JSocket* socket;
                            jlong lastUsed;
                            JConnections* connections;
                            JDataOutputStream* out;
                            JDataInputStream* in;
                            bool opened;
                            JTransport* transport;
                            JGatewayConfiguration* gatewayConfiguration;
                            void sendPing();

                        public:
                            JConnection(JRoute* route, JConnections* connections,JGatewayConfiguration* gatewayConfiguration);
                            JConnection(JSocket* socket, JTransport* transport,JGatewayConfiguration* gatewayConfiguration);
                            static JClass* getClazz();

                            void free();
                            void kill();
                            bool openConnection();
                            void startCall();
                            void finishCall();
                            void sendOk();
                            bool readOk();
                            bool isDead();
                            JDataOutputStream* getOutputStream();
                            JDataInputStream* getInputStream();
                            void setLastUsed();
                            bool isReusable();
                            JSocket* getSocket();
                            jlong getLastUsed();
                            JConnections* getConnections();
                            string toString();
                            ~JConnection();
                    };
                }
            }
        }
    }
}


#endif // JCONNECTION_H
