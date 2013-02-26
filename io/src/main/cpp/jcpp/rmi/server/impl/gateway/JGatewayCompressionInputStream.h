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
                            virtual jint read();
                            virtual jint read(jbyte b[], int off, int len);
                            virtual jbyte peekByte();
                            virtual jbyte readByte();
                            virtual jshort readShort();
                            virtual jushort readUnsignedShort();
                            virtual jint readInt();
                            virtual jlong readLong();
                            virtual float readFloat();
                            virtual double readDouble();
                            virtual char readChar();
                            virtual bool readBool();
                            virtual void close();

                            virtual ~JGatewayCompressionInputStream();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYCOMPRESSIONINPUTSTREAM_H
