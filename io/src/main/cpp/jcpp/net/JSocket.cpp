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
                //throw new JIOException("cannot connect to hot "+host->toString()+" port "+port->toString());
            }
            in=new QtDataInputStream(new QDataStream(socket));//TODO
            out=new QtDataOutputStream(new QDataStream(socket),socket);//TODO
        }

        JSocket::JSocket(QTcpSocket* socket, JServerSocket* serverSocket){
            //TODO set host, port
            this->socket=socket;
            in=new QtDataInputStream(new QDataStream(this->socket));
            out=new QtDataOutputStream(new QDataStream(this->socket),this->socket);
        }

        //TODO
        JInetAddress* JSocket::getInetAddress(){
            return NULL;
        }

        //TODO
        JInetAddress* JSocket::getLocalAddress(){
            return NULL;
        }

        //TODO
        JPrimitiveInt* JSocket::getPort(){
            return NULL;
        }

        //TODO
        JPrimitiveInt* JSocket::getLocalPort(){
            return NULL;
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
            socket->flush();
            socket->close();
        }

        JSocket::~JSocket() {
            delete host;
            delete port;
            delete socket;
            delete in;
            delete out;
        }
    }
}
