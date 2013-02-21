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
            bool bIsClosed;
            JString* host;
            JPrimitiveInt* port;
            JInetAddress* localInetAddress;
            JPrimitiveInt* remotePort;
            JInetAddress* remoteInetAddress;
            QTcpSocket* socket;
            JInputStream* in;
            JOutputStream* out;
            JSocket(JClass* _class);

        public:
            JSocket(JString* host, JPrimitiveInt* port,jint timeout);
            JSocket(QTcpSocket* socket, JServerSocket* serverSocket);
            static JClass* getClazz();

            virtual QObject* getQObject();
            virtual JInetAddress* getInetAddress();
            virtual JInetAddress* getLocalAddress();
            virtual JPrimitiveInt* getPort();
            virtual JPrimitiveInt* getLocalPort();

            virtual JInputStream* getInputStream();
            virtual JOutputStream* getOutputStream();

            virtual void setTcpNoDelay(bool on);
            virtual bool getTcpNoDelay();

            virtual void setSoLinger(bool on, int linger);
            virtual int getSoLinger();

            virtual void setOOBInline(bool on);
            virtual bool getOOBInline();

            virtual void setSoTimeout(int s);
            virtual int getSoTimeout();

            virtual void setSendBufferSize(int size);
            virtual int getSendBufferSize();

            virtual void setReceiveBufferSize(int size);
            virtual int getReceiveBufferSize();

            virtual void setKeepAlive(bool on);
            virtual bool getKeepAlive();

            virtual void setTrafficClass(int tc);
            virtual int getTrafficClass();

            virtual void setReuseAddress(bool on);
            virtual bool getReuseAddress();

            virtual void close();
            virtual bool isClosed();
            ~JSocket();

        };
    }
}
#endif // JSOCKET_H
