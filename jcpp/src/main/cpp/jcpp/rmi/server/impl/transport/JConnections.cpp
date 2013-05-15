#include "JConnections.h"
#include "JSystem.h"
#include "JRoute.h"
#include "JConnection.h"
#include "JTransport.h"
#include "Collections.h"
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JConnectionsClass : public JClass{
                      public:
                        JConnectionsClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.Connections";
                            this->name="jcpp.rmi.server.impl.transport.Connections";
                            this->simpleName="Connections";
                            addInterface(JRunnable::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnections::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionsClass();
                        }
                        return clazz;
                    }

                    JConnections::JConnections(JEndPoint* remoteEndPoint, JTransport* transport){
                        this->remoteEndPoint=remoteEndPoint;
                        this->transport=transport;
                        this->freeConnectionList=new vector<JConnection*>();
                        this->takenConnectionList=new vector<JConnection*>();
                        this->connectionTimeout=transport->getTransportConfiguration()->getConnectionPoolTimeout()->get();
                        launchTimeoutTimer();
                    }

                    JConnection* JConnections::createConnection(){
                        JConnection* connection=NULL;
                        lock();
                        jint socketTimeout = transport->getTransportConfiguration()->getSocketTimeout()->get();
                        while (freeConnectionList->size() > 0) {
                            vector<JConnection*>::iterator it=freeConnectionList->begin();
                            connection = *it;
                            freeConnectionList->erase(it);
                            connection->getSocket()->takeOwner();
                            if (!connection->isDead()) {
                                takenConnectionList->push_back(connection);
                                connection->getSocket()->setSoTimeout(socketTimeout);
                                break;
                            }else{
                                connection->kill();
                            }
                        }
                        if (connection==NULL){
                            JRoute* route = transport->getTransportRouter()->findRoute(transport->getLocalEndPoint()->getSite(), remoteEndPoint);
                            if ((route == NULL) || (route->getAddressList()->size() == 0)) {
                                throw new JIOException("No route found from [" + transport->getLocalEndPoint()->toString() + "] to [" + remoteEndPoint->toString() + "]");
                            }
                            connection = new JConnection(route, this,transport->getTransportConfiguration()->getGatewayConfiguration());
                            takenConnectionList->push_back(connection);
                            connection->getSocket()->setSoTimeout(socketTimeout);
                        }
                        unlock();
                        return connection;
                    }

                    jlong JConnections::getConnectionTimeout(){
                        return connectionTimeout;
                    }

                    void JConnections::freeAll(){
                        lock();
                        for (unsigned int i=0;i<takenConnectionList->size();i++){
                            JConnection* conn=takenConnectionList->at(i);
                            conn->free();
                        }
                        unlock();
                    }

                    void JConnections::killAll(){
                       lock();
                       for (unsigned int i=0;i<takenConnectionList->size();i++){
                           JConnection* conn=takenConnectionList->at(i);
                           conn->kill();
                       }
                       for (unsigned int i=0;i<freeConnectionList->size();i++){
                           JConnection* conn=freeConnectionList->at(i);
                           conn->kill();
                       }
                       takenConnectionList->clear();
                       freeConnectionList->clear();
                       remove();
                       unlock();
                       delete this;
                    }

                    JEndPoint* JConnections::getRemoteEndPoint(){
                        return remoteEndPoint;
                    }

                    JTransport* JConnections::getTransport(){
                        return transport;
                    }

                    void JConnections::free(JConnection* connection){
                        lock();
                        if (deleteFromVector(takenConnectionList,connection)){
                            connection->setLastUsed();
                            freeConnectionList->insert(freeConnectionList->begin(),connection);//TODO test it adds at the beginning
                            connection->getSocket()->releaseOwner();
                        }
                        unlock();
                    }

                    void JConnections::kill(JConnection* connection){
                        lock();
                        deleteFromVector(takenConnectionList,connection);
                        deleteFromVector(freeConnectionList,connection);
                        if (takenConnectionList->empty() && freeConnectionList->empty()){
                            remove();
                        }
                        unlock();
                    }

                    void JConnections::remove(){
                        scheduledFuture->cancel();
                        transport->remove(this);
                    }

                    void JConnections::run(){
                        lock();
                        vector<JConnection*>* freeArray=new vector<JConnection*>(*freeConnectionList);
                        unlock();
                        jlong currentTime=JSystem::currentTimeMillis();
                        for (unsigned int i=0;i<freeArray->size();i++){
                            JConnection* conn=freeArray->at(i);
                            jlong diff = currentTime - conn->getLastUsed();
                            if (diff > getConnectionTimeout()) {
                                try {
                                    conn->kill();
                                } catch (JIOException* ex) {
                                    //TODO log
                                    ex->printStackTrace(&cout);
                                    delete ex;
                                }
                            }
                        }
                        delete freeArray;
                    }

                    void JConnections::launchTimeoutTimer(){
                        scheduledFuture=transport->getScheduledExecutorService()->schedule(this,transport->getTransportConfiguration()->getTimeoutTimerInterval()->get(), transport->getTransportConfiguration()->getTimeoutTimerInterval()->get());
                    }

                    JString JConnections::toString(){
                        return "Connections[localEndPoint="+transport->getLocalEndPoint()->toString()+", removeEndPoint="+remoteEndPoint->toString()+"]";
                    }

                    JConnections::~JConnections(){
                        delete freeConnectionList;
                        delete takenConnectionList;
                    }
                }
            }
        }
    }
}


