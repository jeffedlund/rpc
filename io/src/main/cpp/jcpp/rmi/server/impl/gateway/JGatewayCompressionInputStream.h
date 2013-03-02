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
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayCompressionInputStream : public JInputStream{
                        protected:
                            JGatewayInputStream* gatewayInputStream;

                        public:
                            JGatewayCompressionInputStream(JInputStream* i,JGatewayConfiguration* gatewayConfiguration);

                            static JClass* getClazz();

                            JRoute* getRoute();
                            virtual jlong available();
                            virtual bool waitForReadyRead(int = 30000);
                            virtual jbyte read();
                            virtual jint read(jbyte b[], int off, int len);
                            virtual jbyte peekByte();
                            virtual void close();
                            virtual ~JGatewayCompressionInputStream();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYCOMPRESSIONINPUTSTREAM_H
