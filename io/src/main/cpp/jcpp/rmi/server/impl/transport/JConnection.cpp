#include "JConnection.h"
#include "JTransportConstants.h"
#include "JSystem.h"
#include "JConnections.h"
#include "JTransport.h"
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JConnectionClass : public JClass{
                      public:
                        JConnectionClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.Connection";
                            this->name="jcpp.rmi.server.impl.transport.Connection";
                            this->simpleName="Connection";
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnection::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionClass();
                        }
                        return clazz;
                    }

                    JConnection::JConnection(JRoute* route, JConnections* connections){
                        this->socket=NULL;//TODO GatewaySocketFactory.createSocket(route, connections.getTransport().getTransportConfiguration().getGatewayConfiguration());
                        this->socket->setSoTimeout(0);//TODO connections.getTransport().getTransportConfiguration().getSocketTimeout());
                        this->socket->setTcpNoDelay(true);
                        this->socket->setKeepAlive(true);
                        this->connections=connections;
                    }

                    JConnection::JConnection(JSocket* socket, JTransport* transport){
                        this->socket=socket;
                        this->transport=transport;

                    }

                    void JConnection::free(){
                        if (connections!=NULL){
                            if (isReusable()){
                                connections->free(this);
                            }else{
                                kill();
                            }
                        }
                    }

                    void JConnection::kill(){
                        if (connections!=NULL){
                            connections->kill(this);
                        }
                        socket->close();
                    }

                    bool JConnection::openConnection(){
                        if (!opened){
                            opened=true;
                            getOutputStream();
                            out->writeInt(MAGIC_NUMBER);
                            connections->getTransport()->getLocalEndPoint()->write(out);
                            out->flush();

                            if (isReusable()){
                                jint oldTimeout=socket->getSoTimeout();
                                if (connections==NULL){
                                    //TODO socket.setSoTimeout(transport.getTransportConfiguration().getPingTimeout());
                                }else{
                                    //TODO socket.setSoTimeout(connections.getTransport().getTransportConfiguration().getPingTimeout());
                                }
                                bool b=readOk();
                                socket->setSoTimeout(oldTimeout);
                                return b;
                            }
                        }
                        return true;
                    }

                    void JConnection::startCall(){
                        getOutputStream();
                        out->writeByte((jint)MSG_TYPE_CALL);
                    }

                    void JConnection::finishCall(){
                        getOutputStream();
                        out->flush();
                    }

                    void JConnection::sendOk(){
                        getOutputStream();
                        out->writeByte((jint)MSG_TYPE_OK);
                        if (isReusable()){
                            out->flush();
                        }
                    }

                    bool JConnection::readOk(){
                        getInputStream();
                        jbyte okByte=in->readByte();
                        if (okByte!= MSG_TYPE_OK){
                            return false;
                        }
                        return true;
                    }

                    bool JConnection::isDead(){
                        bool isDead=false;
                        int oldTimeout=socket->getSoTimeout();
                        try{
                            sendPing();
                            if (connections==NULL){
                                //TODO socket.setSoTimeout(transport.getTransportConfiguration().getPingTimeout());
                            } else {
                                //TODO socket.setSoTimeout(connections.getTransport().getTransportConfiguration().getPingTimeout());
                            }
                            if (!readOk()) {
                                isDead = true;
                            }
                        }catch(JIOException* e){
                            isDead=true;
                            //TODO log
                        }
                        if (isDead && !socket->isClosed()){
                            socket->close();
                        }
                        socket->setSoTimeout(oldTimeout);
                        return isDead;
                    }

                    JDataOutputStream* JConnection::getOutputStream(){
                        if (out==NULL){
                            JOutputStream* outputStream=socket->getOutputStream();
                            out=new JDataOutputStream(outputStream);//TODO implemenet bufferedoutputstream
                        }
                        return out;
                    }

                    JDataInputStream* JConnection::getInputStream(){
                        if (in==NULL){
                            JInputStream* inputStream=socket->getInputStream();
                            in=new JDataInputStream(inputStream);
                        }
                        return in;
                    }

                    void JConnection::setLastUsed(){
                        this->lastUsed=JSystem::currentTimeMillis();
                    }

                    bool JConnection::isReusable(){
                        return true;//TODO((IGatewaySocket) socket).isReausable();
                    }

                    JSocket* JConnection::getSocket(){
                        return socket;
                    }

                    jlong JConnection::getLastUsed(){
                        return lastUsed;
                    }

                    JConnections* JConnection::getConnections(){
                        return connections;
                    }

                    string JConnection::toString(){
                        return "Connection["+connections->toString()+","+socket->toString()+"]";
                    }

                    void JConnection::sendPing(){
                        out->writeByte((jint)MSG_TYPE_PING);
                        out->flush();
                    }

                    JConnection::~JConnection(){
                        delete in;
                        delete out;
                    }
                }
            }
        }
    }
}

