#ifndef JGATEWAYCOMPRESSIONOUTPUTSTREAM_H
#define JGATEWAYCOMPRESSIONOUTPUTSTREAM_H

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
#include "JGatewayOutputStream.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JCPP_LIBRARY_EXPORT JGatewayCompressionOutputStream : public JOutputStream{
                        protected:
                            JGatewayOutputStream* gatewayOutputStream;

                        public:
                            JGatewayCompressionOutputStream(JOutputStream* o,JRoute* route);
                            static JClass* getClazz();
                            JRoute* getRoute();
                            virtual void write(jbyte b);
                            virtual void write(jbyte b[], int off, int len);
                            virtual void flush();
                            virtual void close();
                            virtual ~JGatewayCompressionOutputStream();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYCOMPRESSIONOUTPUTSTREAM_H
