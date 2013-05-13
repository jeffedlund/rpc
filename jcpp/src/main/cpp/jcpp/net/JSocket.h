#ifndef JSOCKET_H
#define JSOCKET_H

#include "JInetAddress.h"
#include <QTcpSocket>
#include "JServerSocket.h"
#include "QObjectAware.h"
#include "JInetAddress.h"
#include "JCPP.h"
#include "JInputStream.h"
#include "JOutputStream.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace net{
        class JServerSocket;

        class JCPP_LIBRARY_EXPORT JSocket : public JObject, public QObjectAware{
        protected:
            jbool bIsClosed;
            JString* host;
            JPrimitiveInt* port;
            JInetAddress* localInetAddress;
            JPrimitiveInt* remotePort;
            JInetAddress* remoteInetAddress;
            QTcpSocket* socket;
            JInputStream* in;
            JOutputStream* out;
            JSocket(JClass* _class);
            JSocket(QTcpSocket* socket, JServerSocket* serverSocket);
            friend class JServerSocket;

        public:
            JSocket(JString host, jint port,jint timeout);
            static JClass* getClazz();
            virtual void takeOwner();
            virtual void releaseOwner();
            virtual QObject* getQObject();
            virtual JInetAddress* getInetAddress();
            virtual JInetAddress* getLocalAddress();
            virtual jint getPort();
            virtual jint getLocalPort();
            virtual JInputStream* getInputStream();
            virtual JOutputStream* getOutputStream();
            virtual void setTcpNoDelay(jbool on);
            virtual jbool getTcpNoDelay();
            virtual void setSoLinger(jbool on, jint linger);
            virtual jint getSoLinger();
            virtual void setOOBInline(jbool on);
            virtual jbool getOOBInline();
            virtual void setSoTimeout(jint s);
            virtual jint getSoTimeout();
            virtual void setSendBufferSize(jint size);
            virtual jint getSendBufferSize();
            virtual void setReceiveBufferSize(jint size);
            virtual jint getReceiveBufferSize();
            virtual void setKeepAlive(jbool on);
            virtual jbool getKeepAlive();
            virtual void setTrafficClass(jint tc);
            virtual jint getTrafficClass();
            virtual void setReuseAddress(jbool on);
            virtual jbool getReuseAddress();
            virtual void close();
            virtual jbool isClosed();
            virtual ~JSocket();
        };
    }
}
#endif // JSOCKET_H
