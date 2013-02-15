#ifndef JSOCKET_H
#define JSOCKET_H

#include "JLANG.h"
#include "JInetAddress.h"
#include "JIO.h"
#include <QTcpSocket>

namespace jcpp{
    namespace net{
        class JSocket : public JObject{
        protected:
            QTcpSocket* socket;

        public:
            JSocket(JString* host, JPrimitiveInt* port);

            JInetAddress* getInetAddress();
            JInetAddress* getLocalAddress();
            JPrimitiveInt* getPort();
            JPrimitiveInt* getLocalPort();

            JInputStream* getInputStream();
            JOutputStream* getOutputStream();

            void setTcpNoDelay(bool on);
            bool getTcpNoDelay();

            void setSoLinger(bool on, int linger);
            int getSoLinger();

            void setOOBInline(bool on);
            bool getOOBInline();

            int getSoTimeout();

            void setSendBufferSize(int size);
            int getSendBufferSize();

            void setReceiveBufferSize(int size);
            int getReceiveBufferSize();

            void setKeepAlive(bool on);
            bool getKeepAlive();

            void setTrafficClass(int tc);
            int getTrafficClass();

            void setReuseAddress(bool on);
            bool getReuseAddress();

            void close();

        };
    }
}
#endif // JSOCKET_H
