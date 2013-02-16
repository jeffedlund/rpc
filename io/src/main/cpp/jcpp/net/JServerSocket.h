#ifndef JSERVERSOCKET_H
#define JSERVERSOCKET_H

#include "JLANG.h"
#include "JInetAddress.h"
#include "JIO.h"
#include <QTcpSocket>
#include <QTcpServer>
#include "JSocket.h"

namespace jcpp{
    namespace net{
        class JSocket;

        class JServerSocket : public JObject{
        protected:
            JString* host;
            JPrimitiveInt* port;
            JPrimitiveInt* backlog;


        public:
            QTcpServer* server;
            JServerSocket(JString* host, JPrimitiveInt* port,JPrimitiveInt* backlog);
            static JClass* getClazz();

            JInetAddress* getInetAddress();
            JPrimitiveInt* getLocalPort();
            void connect();
            JSocket* accept();

            void setSoTimeout(int s);
            int getSoTimeout();

            void setReuseAddress(bool on);
            bool getReuseAddress();

            void setReceiveBufferSize(int size);
            int getReceiveBufferSize();

            //TODO static setSocketFactory()

            void close();
            ~JServerSocket();

        };
    }
}

#endif // JSERVERSOCKET_H
