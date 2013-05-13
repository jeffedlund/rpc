#include "JSocket.h"
#include "JIOException.h"
#include "QtDataInputStream.h"
#include "QtDataOutputStream.h"
#include "QObjectHolder.h"

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
        };

        static JClass* clazz;

        JClass* JSocket::getClazz(){
            if (clazz==NULL){
                clazz=new JSocketClass();
            }
            return clazz;
        }

        JSocket::JSocket(JClass* _class):JObject(_class){
            this->bIsClosed=false;
            this->host=NULL;
            this->port=0;
            this->socket=NULL;
            this->localInetAddress=NULL;
            this->remoteInetAddress=NULL;
            this->in=NULL;
            this->out=NULL;
            this->remotePort=NULL;
        }

        JSocket::JSocket(JString host, jint port,jint timeout){
            this->bIsClosed=false;
            this->host=new JString(host);
            this->port=new JPrimitiveInt(port);
            this->socket=new QTcpSocket();
            socket->connectToHost(QString::fromStdString(this->host->getString()),this->port->get());
            while (!socket->waitForConnected(300000)){//TODO use timeout
                timeout=timeout;
                //throw new JIOException("cannot connect to hot "+host->toString()+" port "+port->toString());
            }
            this->localInetAddress=new JInetAddress(socket->localAddress().toString().toStdString());
            this->remoteInetAddress=new JInetAddress(socket->peerAddress().toString().toStdString());
            this->in=new QtDataInputStream(new QDataStream(socket));
            this->out=new QtDataOutputStream(new QDataStream(socket),socket);
            this->remotePort=new JPrimitiveInt(socket->peerPort());
        }

        JSocket::JSocket(QTcpSocket* socket, JServerSocket* serverSocket){
            this->bIsClosed=false;
            this->host=new JString(serverSocket->getInetAddress()->getHostName());
            this->port=new JPrimitiveInt(serverSocket->getLocalPort());
            this->socket=socket;
            this->localInetAddress=new JInetAddress(socket->localAddress().toString().toStdString());
            this->remoteInetAddress=new JInetAddress(socket->peerAddress().toString().toStdString());
            this->in=new QtDataInputStream(new QDataStream(this->socket));
            this->out=new QtDataOutputStream(new QDataStream(this->socket),this->socket);
            this->remotePort=new JPrimitiveInt(socket->peerPort());
        }

        void JSocket::takeOwner(){
            QObjectHolder::getQObjectHolder()->takeOwner(getQObject());
        }

        void JSocket::releaseOwner(){
            QObjectHolder::getQObjectHolder()->releaseOwner(getQObject());
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

        jint JSocket::getPort(){
            return remotePort->get();
        }

        jint JSocket::getLocalPort(){
            return this->port->get();
        }

        JInputStream* JSocket::getInputStream(){
            return in;
        }

        JOutputStream* JSocket::getOutputStream(){
            return out;
        }

        void JSocket::setTcpNoDelay(jbool on){
            socket->setSocketOption(QAbstractSocket::LowDelayOption,QVariant(on));
        }

        bool JSocket::getTcpNoDelay(){
            QVariant v=socket->socketOption(QAbstractSocket::LowDelayOption);
            return v.toBool();
        }

        //TODO
        void JSocket::setSoLinger(jbool, jint){
        }

        //TODO
        jint JSocket::getSoLinger(){
            return 0;
        }

        //TODO
        void JSocket::setOOBInline(jbool){
        }

        //TODO
        jbool JSocket::getOOBInline(){
            return false;
        }

        void JSocket::setSoTimeout(jint){
        }

        //TODO
        jint JSocket::getSoTimeout(){
            return 0;
        }

        //TODO
        void JSocket::setSendBufferSize(jint){
        }

        //TODO
        jint JSocket::getSendBufferSize(){
            return 0;
        }

        void JSocket::setReceiveBufferSize(jint size){
            socket->setReadBufferSize(size);
        }

        jint JSocket::getReceiveBufferSize(){
            return socket->readBufferSize();
        }

        void JSocket::setKeepAlive(jbool on){
            socket->setSocketOption(QAbstractSocket::KeepAliveOption, QVariant(on));
        }

        jbool JSocket::getKeepAlive(){
            QVariant v=socket->socketOption(QAbstractSocket::KeepAliveOption);
            return v.toBool();
        }

        //TODO
        void JSocket::setTrafficClass(jint){
        }

        //TODO
        jint JSocket::getTrafficClass(){
            return 0;
        }

        //TODO
        void JSocket::setReuseAddress(jbool){
        }

        //TODO
        jbool JSocket::getReuseAddress(){
            return false;
        }

        void JSocket::close(){
            lock();
            bIsClosed=true;
            if (socket!=NULL && socket->thread()==QThread::currentThread()){
                socket->flush();
            }
            if (in!=NULL){
                in->close();
            }
            if (out!=NULL){
                out->close();
            }
            if (socket!=NULL && socket->thread()==QThread::currentThread()){
                socket->close();
                socket=NULL;
            }
            unlock();
        }

        jbool JSocket::isClosed(){
            lock();
            jbool b=bIsClosed;
            unlock();
            return b;
        }

        JSocket::~JSocket() {
            QObjectHolder::getQObjectHolder()->deleteObject(getQObject());
            delete host;
            delete port;
            delete socket;
            delete localInetAddress;
            delete remoteInetAddress;
            delete in;
            delete out;
            delete remotePort;
        }
    }
}
