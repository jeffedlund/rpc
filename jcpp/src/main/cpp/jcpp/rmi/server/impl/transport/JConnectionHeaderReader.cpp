#include "JConnectionHeaderReader.h"
#include "JSystem.h"
#include "JDataInputStream.h"
#include "JConnection.h"
#include "JITransportDispatcher.h"
#include "JIGatewaySocket.h"
#include "JEOFException.h"
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JConnectionHeaderReaderClass : public JClass{
                      public:
                        JConnectionHeaderReaderClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.ConnectionHeaderReader";
                            this->name="jcpp.rmi.server.impl.transport.ConnectionHeaderReader";
                            this->simpleName="ConnectionHeaderReader";
                            addInterface(JRunnable::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnectionHeaderReader::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionHeaderReaderClass();
                        }
                        return clazz;
                    }

                    JConnectionHeaderReader::JConnectionHeaderReader(JSocket* socket, JTransport* transport):JObject(getClazz()){
                        this->socket=socket;
                        this->transport=transport;
                        socket->releaseOwner();
                    }

                    void JConnectionHeaderReader::unexport(){
                        if (socket!=NULL){
                            socket->close();
                        }
                    }

                    void JConnectionHeaderReader::run(){
                        JIGatewaySocket* s=dynamic_cast<JIGatewaySocket*>(socket);
                        socket->takeOwner();
                        JConnection* connection = NULL;
                        JDataInputStream* in = new JDataInputStream(socket->getInputStream());
                        jint magicNumber = in->readInt();
                        if (magicNumber != JTransportConfiguration::MAGIC_NUMBER) {
                            delete in;
                            throw new JEOFException();
                        }
                        JEndPoint* remoteEndPoint = new JEndPoint(in);//TODO lifecycle  of remtoeEndPoint? when to delete
                        connection = new JConnection(socket, transport, transport->getTransportConfiguration()->getGatewayConfiguration());

                        if (connection->isReusable()) {
                            connection->sendOk();
                        }
                        do{
                            jbyte msgType = in->readByte();
                            if (msgType == JTransportConfiguration::MSG_TYPE_PING) {
                                connection->sendOk();
                                if (!connection->isReusable()) {
                                    connection->getOutputStream()->flush();
                                }

                            } else if (msgType == JTransportConfiguration::MSG_TYPE_CALL) {
                                transport->getTransportDispatcher()->dispatch(remoteEndPoint, transport->getLocalEndPoint(), connection);

                                if (!connection->isReusable()) {
                                    connection->sendOk();
                                }
                                connection->getOutputStream()->flush();
                            } else {
                                throw new JEOFException();
                            }

                        } while (!socket->isClosed() && s->isReusable());

                        if (connection != NULL) {
                            connection->kill();
                        }
                        transport->remove(this);
                        delete connection;
                        delete this;
                    }

                    JConnectionHeaderReader::~JConnectionHeaderReader(){
                    }
                }
            }
        }
    }
}
