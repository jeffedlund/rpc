#ifndef JSERVERSOCKET_H
#define JSERVERSOCKET_H

#include "JLANG.h"
#include "JInetAddress.h"
#include "JIO.h"
#include <QTcpSocket>
#include <QTcpServer>
#include "JSocket.h"
#include "QObjectAware.h"

namespace jcpp{
    namespace net{
        class JSocket;

        class JServerSocket : public JObject, public QObjectAware{
        protected:
            bool bIsClosed;
            JString* host;
            JPrimitiveInt* port;
            JPrimitiveInt* backlog;
            JInetAddress* localInetAddress;
            QTcpServer* server;

        public:
            JServerSocket(JString* host, JPrimitiveInt* port,JPrimitiveInt* backlog);
            static JClass* getClazz();

            virtual QObject* getQObject();
            JInetAddress* getInetAddress();
            JPrimitiveInt* getLocalPort();
            void connect();
            virtual JSocket* accept();

            void setSoTimeout(int s);
            int getSoTimeout();

            void setReuseAddress(bool on);
            bool getReuseAddress();

            void setReceiveBufferSize(int size);
            int getReceiveBufferSize();

            //TODO static setSocketFactory()

            void close();
            bool isClosed();
            ~JServerSocket();

        };
    }
}

#endif // JSERVERSOCKET_H
