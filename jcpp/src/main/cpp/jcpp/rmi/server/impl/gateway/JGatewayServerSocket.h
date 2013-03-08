#ifndef JGATEWAYSERVERSOCKET_H
#define JGATEWAYSERVERSOCKET_H

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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JCPP_LIBRARY_EXPORT JGatewayServerSocket : public JServerSocket{
                        protected:
                            JGatewayConfiguration* gatewayConfiguration;

                        public:
                            JGatewayServerSocket(JString* host, JPrimitiveInt* port,JGatewayConfiguration* gatewayConfiguration);
                            static JClass* getClazz();
                            virtual JSocket* accept();
                            string toString();
                            virtual ~JGatewayServerSocket();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYSERVERSOCKET_H
