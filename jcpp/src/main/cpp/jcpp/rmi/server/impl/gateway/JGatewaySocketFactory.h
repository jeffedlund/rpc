#ifndef JGATEWAYSOCKETFACTORY_H
#define JGATEWAYSOCKETFACTORY_H

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
#include "JGatewayConfiguration.h"
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
                    class JCPP_LIBRARY_EXPORT JGatewaySocketFactory : public JObject{
                        public:
                        static JClass* getClazz();
                        static JSocket* createSocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration);
                        static JServerSocket* createServerSocket(JString host, jint port,JGatewayConfiguration* gatewayConfiguration);
                        virtual ~JGatewaySocketFactory();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYSOCKETFACTORY_H
