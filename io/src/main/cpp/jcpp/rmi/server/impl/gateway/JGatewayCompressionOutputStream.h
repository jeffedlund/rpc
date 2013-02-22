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
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayCompressionOutputStream : public JOutputStream{
                        protected:
                            JGatewayOutputStream* gatewayOutputStream;

                        public:
                            JGatewayCompressionOutputStream(JOutputStream* o,JRoute* route);
                            static JClass* getClazz();
                            JRoute* getRoute();
                            virtual void write(jint b);
                            virtual void write(jbyte b[]);
                            virtual void write(jbyte b[], int off, int len);
                            virtual void flush();
                            virtual void close();
                            virtual void writeBoolean(bool v);
                            virtual void writeByte(jbyte v);
                            virtual void writeShort(jshort v);
                            virtual void writeChar(jushort v);
                            virtual void writeInt(jint v);
                            virtual void writeLong(jlong v);
                            virtual void writeFloat(float v);
                            virtual void writeDouble(double v);
                            ~JGatewayCompressionOutputStream();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYCOMPRESSIONOUTPUTSTREAM_H
