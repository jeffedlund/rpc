#ifndef JSOCKET_H
#define JSOCKET_H

#include "JLANG.h"
#include "JInetAddress.h"
#include "JIO.h"
#include <QTcpSocket>
#include "JServerSocket.h"
#include "QObjectAware.h"
#include "JInetAddress.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace net{
        class JServerSocket;

        class JSocket : public JObject, public QObjectAware{
        protected:
            JString* host;
            JPrimitiveInt* port;
            JInetAddress* localInetAddress;
            JPrimitiveInt* remotePort;
            JInetAddress* remoteInetAddress;
            QTcpSocket* socket;
            JInputStream* in;
            JOutputStream* out;

        public:
            JSocket(JString* host, JPrimitiveInt* port);
            JSocket(QTcpSocket* socket, JServerSocket* serverSocket);
            static JClass* getClazz();

            virtual QObject* getQObject();
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

            void setSoTimeout(int s);
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
            ~JSocket();

        };
    }
}
#endif // JSOCKET_H
