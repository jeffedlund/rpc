#ifndef JGATEWAYCOMPRESSIONINPUTSTREAM_H
#define JGATEWAYCOMPRESSIONINPUTSTREAM_H

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
#include "JGatewayInputStream.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JCPP_LIBRARY_EXPORT JGatewayCompressionInputStream : public JFilterInputStream{
                        protected:
                            JGatewayInputStream* gatewayInputStream;

                        public:
                            JGatewayCompressionInputStream(JInputStream* i,JGatewayConfiguration* gatewayConfiguration);
                            static JClass* getClazz();
                            JRoute* getRoute();
                            virtual ~JGatewayCompressionInputStream();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYCOMPRESSIONINPUTSTREAM_H
