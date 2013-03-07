#ifndef JSERVERSOCKET_H
#define JSERVERSOCKET_H

#include "JLANG.h"
#include "JInetAddress.h"
#include "JIO.h"
#include <QTcpSocket>
#include <QTcpServer>
#include "JSocket.h"
#include "JCPP.h"

namespace jcpp{
    namespace net{
        class JSocket;

        class JCPP_LIBRARY_EXPORT JServerSocket : public JObject, public QObjectAware{
        protected:
            bool bIsClosed;
            JString* host;
            JPrimitiveInt* port;
            JPrimitiveInt* backlog;
            JInetAddress* localInetAddress;
            QTcpServer* server;
            JServerSocket(JString* host, JPrimitiveInt* port,JPrimitiveInt* backlog,JClass* _class);
            bool isListening();
            bool waitForNewConnection(int m, bool* t);
            QTcpSocket* nextPendingConnection();

        public:
            JServerSocket(JString* host, JPrimitiveInt* port,JPrimitiveInt* backlog);
            static JClass* getClazz();

            virtual void takeOwner();
            virtual void releaseOwner();
            virtual QObject* getQObject();
            virtual JInetAddress* getInetAddress();
            virtual JPrimitiveInt* getLocalPort();
            virtual void connect();
            virtual JSocket* accept();

            virtual void setSoTimeout(int s);
            virtual int getSoTimeout();

            virtual void setReuseAddress(bool on);
            virtual bool getReuseAddress();

            virtual void setReceiveBufferSize(int size);
            virtual int getReceiveBufferSize();

            //TODO static setSocketFactory()

            virtual void close();
            virtual bool isClosed();
            virtual ~JServerSocket();

        };
    }
}

#endif // JSERVERSOCKET_H
