#include "JGatewaySocket.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewaySocketClass : public JClass{
                      public:
                        JGatewaySocketClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.GatewaySocket";
                            this->name="jcpp.rmi.server.impl.gateway.GatewaySocket";
                            this->simpleName="GatewaySocket";
                            addInterface(JIGatewaySocket::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JSocket::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JGatewaySocket::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGatewaySocketClass();
                        }
                        return clazz;
                    }

                    JGatewaySocket::JGatewaySocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration):JSocket(getClazz()){
                        JAddress* address = route->popAddress();
                        this->gatewayConfiguration = gatewayConfiguration;
                        this->socket = new JSocket(*address->getHostName(),address->getPort(),gatewayConfiguration->getConnectionTimeout()->get());//TODO
                        this->output = new JGatewayCompressionOutputStream(socket->getOutputStream(), route);
                        this->input = socket->getInputStream();
                        this->bSendSocket = true;
                        this->route = route;
                        setSocketSetting();
                    }

                    JGatewaySocket::JGatewaySocket(JSocket* socket,JInputStream* in,JGatewayConfiguration* gatewayConfiguration):JSocket(getClazz()){
                        this->socket = socket;
                        this->gatewayConfiguration = gatewayConfiguration;
                        this->output = socket->getOutputStream();
                        this->input = new JGatewayCompressionInputStream(in, gatewayConfiguration);
                        this->bSendSocket = false;
                        this->route = ((JGatewayCompressionInputStream*) input)->getRoute();
                        this->input = input;
                        setSocketSetting();
                    }

                    JRoute* JGatewaySocket::getRoute(){
                        return route;
                    }

                    bool JGatewaySocket::isReusable(){
                        return true;
                    }

                    QObject* JGatewaySocket::getQObject(){
                        return socket->getQObject();
                    }

                    JInetAddress* JGatewaySocket::getInetAddress(){
                        return socket->getInetAddress();
                    }

                    JInetAddress* JGatewaySocket::getLocalAddress(){
                        return socket->getLocalAddress();
                    }

                    jint JGatewaySocket::getPort(){
                        return socket->getPort();
                    }

                    jint JGatewaySocket::getLocalPort(){
                        return socket->getLocalPort();
                    }

                    JInputStream* JGatewaySocket::getInputStream(){
                        return input;
                    }

                    JOutputStream* JGatewaySocket::getOutputStream(){
                        return output;
                    }

                    void JGatewaySocket::setTcpNoDelay(bool on){
                        socket->setTcpNoDelay(on);
                    }

                    bool JGatewaySocket::getTcpNoDelay(){
                        return socket->getTcpNoDelay();
                    }

                    void JGatewaySocket::setSoLinger(bool on, int linger){
                        socket->setSoLinger(on,linger);
                    }

                    int JGatewaySocket::getSoLinger(){
                        return socket->getSoLinger();
                    }

                    void JGatewaySocket::setOOBInline(bool on){
                        socket->setOOBInline(on);
                    }

                    bool JGatewaySocket::getOOBInline(){
                        return socket->getOOBInline();
                    }

                    void JGatewaySocket::setSoTimeout(int s){
                        socket->setSoTimeout(s);
                    }

                    int JGatewaySocket::getSoTimeout(){
                        return socket->getSoTimeout();
                    }

                    void JGatewaySocket::setSendBufferSize(int size){
                        socket->setSendBufferSize(size);
                    }

                    int JGatewaySocket::getSendBufferSize(){
                        return socket->getSendBufferSize();
                    }

                    void JGatewaySocket::setReceiveBufferSize(int size){
                        socket->setReceiveBufferSize(size);
                    }

                    int JGatewaySocket::getReceiveBufferSize(){
                        return socket->getReceiveBufferSize();
                    }

                    void JGatewaySocket::setKeepAlive(bool on){
                        socket->setKeepAlive(on);
                    }

                    bool JGatewaySocket::getKeepAlive(){
                        return socket->getKeepAlive();
                    }

                    void JGatewaySocket::setTrafficClass(int tc){
                        socket->setTrafficClass(tc);
                    }

                    int JGatewaySocket::getTrafficClass(){
                        return socket->getTrafficClass();
                    }

                    void JGatewaySocket::setReuseAddress(bool on){
                        socket->setReuseAddress(on);
                    }

                    bool JGatewaySocket::getReuseAddress(){
                        return socket->getReuseAddress();
                    }

                    void JGatewaySocket::close(){
                        output->close();
                        input->close();
                        socket->close();
                        JSocket::close();
                    }

                    bool JGatewaySocket::isClosed(){
                        return socket->isClosed();
                    }

                    JString JGatewaySocket::toString(){
                        JString strSocketType = "GatewaySocket";
                        strSocketType += bSendSocket ? "(SendSocket)" : "(ReceiveSocket)";
                        return strSocketType + "[socket:" + socket->toString() + "]";
                    }

                    void JGatewaySocket::setSocketSetting(){
                        socket->setSoTimeout(gatewayConfiguration->getReadTimeout()->get());
                    }

                    JGatewaySocket::~JGatewaySocket(){
                        delete socket;
                        delete output;
                        delete input;
                        delete route;
                    }
                }
            }
        }
    }
}

