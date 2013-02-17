#include "JSocket.h"
#include "JIOException.h"
#include "QtDataInputStream.h"
#include "QtDataOutputStream.h"

namespace jcpp{
    namespace net{
        class JSocketClass : public JClass{
        public:
          JSocketClass(){
              this->canonicalName="java.net.Socket";
              this->name="java.lang.Socket";
              this->simpleName="Socket";
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JSocket::getClazz(){
            if (clazz==NULL){
                clazz=new JSocketClass();
            }
            return clazz;
        }

        JSocket::JSocket(JString* host, JPrimitiveInt* port){
            this->host=host;
            this->port=port;
            this->socket=new QTcpSocket();
            socket->connectToHost(QString::fromStdString(host->getString()),port->get());
            while (!socket->waitForConnected(300000)){
                //TODO use connection timeout stuff
                //throw new JIOException("cannot connect to hot "+host->toString()+" port "+port->toString());
            }
            this->localInetAddress=new JInetAddress(new JString(socket->localAddress().toString().toStdString()));
            this->remoteInetAddress=new JInetAddress(new JString(socket->peerAddress().toString().toStdString()));
            this->in=new QtDataInputStream(new QDataStream(socket));
            this->out=new QtDataOutputStream(new QDataStream(socket),socket);
            this->remotePort=new JPrimitiveInt(socket->peerPort());
        }

        JSocket::JSocket(QTcpSocket* socket, JServerSocket* serverSocket){
            this->host=serverSocket->getInetAddress()->getHostName();
            this->port=serverSocket->getLocalPort();
            this->socket=socket;
            this->localInetAddress=new JInetAddress(new JString(socket->localAddress().toString().toStdString()));
            this->remoteInetAddress=new JInetAddress(new JString(socket->peerAddress().toString().toStdString()));
            this->in=new QtDataInputStream(new QDataStream(this->socket));
            this->out=new QtDataOutputStream(new QDataStream(this->socket),this->socket);
            this->remotePort=new JPrimitiveInt(socket->peerPort());
        }

        QObject* JSocket::getQObject(){
            return socket;
        }

        JInetAddress* JSocket::getInetAddress(){
            return remoteInetAddress;
        }

        JInetAddress* JSocket::getLocalAddress(){
            return localInetAddress;
        }

        JPrimitiveInt* JSocket::getPort(){
            return remotePort;
        }

        JPrimitiveInt* JSocket::getLocalPort(){
            return this->port;
        }

        JInputStream* JSocket::getInputStream(){
            return in;
        }

        JOutputStream* JSocket::getOutputStream(){
            return out;
        }

        void JSocket::setTcpNoDelay(bool on){
            socket->setSocketOption(QAbstractSocket::LowDelayOption,QVariant(on));
        }

        bool JSocket::getTcpNoDelay(){
            QVariant v=socket->socketOption(QAbstractSocket::LowDelayOption);
            return v.toBool();
        }

        //TODO
        void JSocket::setSoLinger(bool on, int linger){
        }

        //TODO
        int JSocket::getSoLinger(){
            return 0;
        }

        //TODO
        void JSocket::setOOBInline(bool on){
        }

        //TODO
        bool JSocket::getOOBInline(){
            return false;
        }

        void JSocket::setSoTimeout(int s){
        }

        //TODO
        int JSocket::getSoTimeout(){
            return 0;
        }

        //TODO
        void JSocket::setSendBufferSize(int size){
        }

        //TODO
        int JSocket::getSendBufferSize(){
            return 0;
        }

        void JSocket::setReceiveBufferSize(int size){
            socket->setReadBufferSize(size);
        }

        int JSocket::getReceiveBufferSize(){
            return socket->readBufferSize();
        }

        void JSocket::setKeepAlive(bool on){
            socket->setSocketOption(QAbstractSocket::KeepAliveOption, QVariant(on));
        }

        bool JSocket::getKeepAlive(){
            QVariant v=socket->socketOption(QAbstractSocket::KeepAliveOption);
            return v.toBool();
        }

        //TODO
        void JSocket::setTrafficClass(int tc){
        }

        //TODO
        int JSocket::getTrafficClass(){
            return 0;
        }

        //TODO
        void JSocket::setReuseAddress(bool on){
        }

        //TODO
        bool JSocket::getReuseAddress(){
            return false;
        }

        void JSocket::close(){
            in->close();
            out->close();
            socket->flush();
            socket->close();
        }

        JSocket::~JSocket() {
            delete socket;
            delete localInetAddress;
            delete remoteInetAddress;
            delete in;
            delete out;
            delete remotePort;
        }
    }
}
