#include "JServerSocket.h"
#include "JIOException.h"
#include "QtDataInputStream.h"
#include "QtDataOutputStream.h"

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

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JServerSocket::getClazz(){
            if (clazz==NULL){
                clazz=new JServerSocketClass();
            }
            return clazz;
        }

        JServerSocket::JServerSocket(JString* host, JPrimitiveInt* port,JPrimitiveInt* backlog){
            this->host=host;
            this->port=port;
            this->backlog=backlog;
            server=new QTcpServer();
            server->setMaxPendingConnections(backlog->get());
        }

        JInetAddress* JServerSocket::getInetAddress(){
            return NULL;
        }

        JPrimitiveInt* JServerSocket::getLocalPort(){
            return NULL;
        }

        void JServerSocket::connect(){
            if (!server->listen(QHostAddress(QString::fromStdString(host->getString())),port->get())){
                throw new JIOException("cannot connect server socket on "+toString());
            }
        }

        JSocket* JServerSocket::accept(){
            while (true){//TODO closed ou non
                if (server->waitForNewConnection(100000,NULL)){
                    QTcpSocket* socket=server->nextPendingConnection();
                    return new JSocket(socket,this);
                }
            }
            return NULL;
        }

        void JServerSocket::setSoTimeout(int s){
        }

        int JServerSocket::getSoTimeout(){
            return 0;
        }

        void JServerSocket::setReuseAddress(bool on){
        }

        bool JServerSocket::getReuseAddress(){
            return false;
        }

        void JServerSocket::setReceiveBufferSize(int size){
        }

        int JServerSocket::getReceiveBufferSize(){
            return 0;
        }

        void JServerSocket::close(){
            server->close();
        }

        JServerSocket::~JServerSocket() {
            delete host;
            delete port;
            delete backlog;
        }
    }
}
