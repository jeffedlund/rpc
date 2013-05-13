#ifndef JSERVERSOCKET_H
#define JSERVERSOCKET_H

#include "JInetAddress.h"
#include <QTcpSocket>
#include <QTcpServer>
#include "JSocket.h"
#include "JCPP.h"
#include "JInputStream.h"
#include "JOutputStream.h"
#include "JObject.h"
#include "QObjectAware.h"

namespace jcpp{
    namespace net{
        class JSocket;

        class JCPP_LIBRARY_EXPORT JServerSocket : public JObject, public QObjectAware{
        protected:
            jbool bIsClosed;
            JString* host;
            JPrimitiveInt* port;
            JPrimitiveInt* backlog;
            JInetAddress* localInetAddress;
            QTcpServer* server;
            JServerSocket(JString host, jint port,jint backlog,JClass* _class);
            bool isListening();
            bool waitForNewConnection(int m, bool* t);
            QTcpSocket* nextPendingConnection();

        public:
            JServerSocket(JString host, jint port,jint backlog);
            static JClass* getClazz();
            virtual void takeOwner();
            virtual void releaseOwner();
            virtual QObject* getQObject();
            virtual JInetAddress* getInetAddress();
            virtual jint getLocalPort();
            virtual void connect();
            virtual JSocket* accept();
            virtual void setSoTimeout(jint s);
            virtual jint getSoTimeout();
            virtual void setReuseAddress(jbool on);
            virtual jbool getReuseAddress();
            virtual void setReceiveBufferSize(jint size);
            virtual jint getReceiveBufferSize();
            //TODO static setSocketFactory()
            virtual void close();
            virtual jbool isClosed();
            virtual ~JServerSocket();
        };
    }
}

#endif // JSERVERSOCKET_H
