#include "JSocket.h"

namespace jcpp{
    namespace net{
        JSocket::JSocket(JString* host, JPrimitiveInt* port){//TODO
            this->socket=new QTcpSocket();
            socket->connectToHost(QString::fromStdString(host->getString()),port->get());
            if (!socket->waitForConnected(-1)){
                throw "TODO Error";
            }
        }

        JInetAddress* JSocket::getInetAddress(){
            return NULL;
        }

        JInetAddress* JSocket::getLocalAddress(){
            return NULL;
        }

        JPrimitiveInt* JSocket::getPort(){
            return NULL;
        }

        JPrimitiveInt* JSocket::getLocalPort(){
            return NULL;
        }

        JInputStream* JSocket::getInputStream(){
            return NULL;
        }

        JOutputStream* JSocket::getOutputStream(){
            return NULL;
        }

        void JSocket::setTcpNoDelay(bool on){
            socket->setSocketOption(QAbstractSocket::LowDelayOption,QVariant(on));
        }

        bool JSocket::getTcpNoDelay(){
            QVariant v=socket->socketOption(QAbstractSocket::LowDelayOption);
            return v.toBool();
        }

        void JSocket::setSoLinger(bool on, int linger){

        }

        int JSocket::getSoLinger(){
            return 0;
        }

        void JSocket::setOOBInline(bool on){
        }

        bool JSocket::getOOBInline(){
            return false;
        }

        int JSocket::getSoTimeout(){
            return 0;
        }

        void JSocket::setSendBufferSize(int size){
        }

        int JSocket::getSendBufferSize(){
            return 0;
        }

        void JSocket::setReceiveBufferSize(int size){
        }

        int JSocket::getReceiveBufferSize(){
            return 0;
        }

        void JSocket::setKeepAlive(bool on){
            socket->setSocketOption(QAbstractSocket::KeepAliveOption, QVariant(on));
        }

        bool JSocket::getKeepAlive(){
            QVariant v=socket->socketOption(QAbstractSocket::KeepAliveOption);
            return v.toBool();
        }

        void JSocket::setTrafficClass(int tc){
        }

        int JSocket::getTrafficClass(){
            return 0;
        }

        void JSocket::setReuseAddress(bool on){
        }

        bool JSocket::getReuseAddress(){
            return false;
        }

        void JSocket::close(){
        }
    }
}
