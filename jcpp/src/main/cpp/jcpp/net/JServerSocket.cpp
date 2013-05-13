#include "JServerSocket.h"
#include "JIOException.h"
#include "QtDataInputStream.h"
#include "QtDataOutputStream.h"
#include "QObjectHolder.h"

namespace jcpp{
    namespace net{
        class JServerSocketClass : public JClass{
        public:
          JServerSocketClass(){
              this->canonicalName="java.net.ServerSocket";
              this->name="java.lang.ServerSocket";
              this->simpleName="ServerSocket";
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JServerSocket::getClazz(){
            if (clazz==NULL){
                clazz=new JServerSocketClass();
            }
            return clazz;
        }

        JServerSocket::JServerSocket(JString host, jint port,jint backlog,JClass* _class):JObject(_class){
            this->bIsClosed=false;
            this->host=new JString(host);
            this->port=new JPrimitiveInt(port);
            this->backlog=new JPrimitiveInt(backlog);
            this->server=new QTcpServer();
            this->server->setMaxPendingConnections(backlog);
            this->localInetAddress=new JInetAddress(server->serverAddress().toString().toStdString());
        }

        JServerSocket::JServerSocket(JString host, jint port,jint backlog):JObject(getClazz()){
            this->bIsClosed=false;
            this->host=new JString(host);
            this->port=new JPrimitiveInt(port);
            this->backlog=new JPrimitiveInt(backlog);
            server=new QTcpServer();
            server->setMaxPendingConnections(backlog);
            this->localInetAddress=new JInetAddress(server->serverAddress().toString().toStdString());
        }

        void JServerSocket::takeOwner(){
            QObjectHolder::getQObjectHolder()->takeOwner(getQObject());
        }

        void JServerSocket::releaseOwner(){
            QObjectHolder::getQObjectHolder()->releaseOwner(getQObject());
        }

        QObject* JServerSocket::getQObject(){
            return server;
        }

        JInetAddress* JServerSocket::getInetAddress(){
            return localInetAddress;
        }

        jint JServerSocket::getLocalPort(){
            return port->get();
        }

        void JServerSocket::connect(){
            if (!server->listen(QHostAddress(QString::fromStdString(host->getString())),port->get())){
                throw new JIOException("cannot connect server socket on "+toString());
            }
        }

        JSocket* JServerSocket::accept(){
            while (server->isListening()){//TODO check error on all io operations
                if (server->waitForNewConnection(100000,NULL)){
                    QTcpSocket* socket=server->nextPendingConnection();
                    return new JSocket(socket,this);
                }
            }
            return NULL;
        }

        void JServerSocket::setSoTimeout(jint){//TODO
        }

        jint JServerSocket::getSoTimeout(){
            return 0;
        }

        void JServerSocket::setReuseAddress(jbool){//TODO
        }

        jbool JServerSocket::getReuseAddress(){
            return false;
        }

        void JServerSocket::setReceiveBufferSize(jint){//TODO
        }

        jint JServerSocket::getReceiveBufferSize(){
            return 0;
        }

        void JServerSocket::close(){//TODO
            bIsClosed=true;
            server->close();
        }

        jbool JServerSocket::isClosed(){
            return bIsClosed;
        }

        JServerSocket::~JServerSocket() {
            QObjectHolder::getQObjectHolder()->deleteObject(getQObject());
            delete host;
            delete port;
            delete backlog;
            delete server;
            delete localInetAddress;
        }
    }
}
