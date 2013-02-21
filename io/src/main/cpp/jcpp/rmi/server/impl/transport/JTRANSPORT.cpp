#include "JTransport.h"
#include "JSystem.h"
#include "Collections.h"
#include "JConnectionHeaderReader.h"
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JTransportClass : public JClass{
                      public:
                        JTransportClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.Transport";
                            this->name="jcpp.rmi.server.impl.transport.Transport";
                            this->simpleName="Transport";
                            addInterface(JRunnable::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JTransport::getClazz(){
                        if (clazz==NULL){
                            clazz=new JTransportClass();
                        }
                        return clazz;
                    }

                    static bool less(JEndPoint* e1, JEndPoint* e2){
                        if (e1->getSite()->getString()<e2->getSite()->getString()){
                            if (e1->getAddress()->getHostName()<e2->getAddress()->getHostName()){
                                if (e1->getAddress()->getPort()<e2->getAddress()->getPort()){
                                    return true;
                                }
                            }
                        }
                        return false;
                    }

                    JTransport::JTransport(JEndPoint* localEndPoint,JITransportRouter* transportRouter,JITransportDispatcher* transportDispatcher,JExecutorService* executorService,JScheduledExecutorService* scheduledExecutorService){
                        this->localEndPoint=localEndPoint;
                        this->transportRouter=transportRouter;
                        this->transportDispatcher=transportDispatcher;
                        this->scheduledExecutorService=scheduledExecutorService;
                        this->remoteConnectionsMap=new map<JEndPoint*,JConnections*>();//TODO use correct key comparator
                        this->connectionReaders=new vector<JConnectionHeaderReader*>();
                        this->executorService=executorService;
                    }

                    JConnections* JTransport::getConnections(JEndPoint* remoteEndPoint){
                        JConnections* connections=NULL;
                        lock();
                        connections=getFromMap(remoteConnectionsMap,remoteEndPoint);
                        if (connections==NULL){
                            connections=new JConnections(remoteEndPoint,this);
                            remoteConnectionsMap->insert(pair<JEndPoint*,JConnections*>(remoteEndPoint,connections));
                        }
                        unlock();
                        return connections;
                    }

                    JEndPoint* JTransport::getLocalEndPoint(){
                        return localEndPoint;
                    }

                    JScheduledExecutorService* JTransport::getScheduledExecutorService(){
                        return scheduledExecutorService;
                    }

                    JITransportDispatcher* JTransport::getTransportDispatcher(){
                        return transportDispatcher;
                    }

                    JITransportRouter* JTransport::getTransportRouter(){
                        return transportRouter;
                    }

                    void JTransport::startExport(){
                        serverSocket = NULL;//TODO GatewaySocketFactory.createServerSocket(localEndPoint.getPort(), transportConfiguration.getGatewayConfiguration());
                        localEndPoint->getAddress()->setPPort(serverSocket->getLocalPort());
                        future=executorService->submit(this);
                    }

                    void JTransport::run(){
                        while ((serverSocket != NULL) && !serverSocket->isClosed()) {
                            JSocket* socket = serverSocket->accept();
                            JConnectionHeaderReader* connectionHeaderReader = new JConnectionHeaderReader(socket, this);
                            lock();
                            connectionReaders->push_back(connectionHeaderReader);
                            unlock();
                            executorService->submit(connectionHeaderReader);
                        }
                    }

                    void JTransport::stopExport(){
                        lock();
                        deleteMapOfValuePointer(remoteConnectionsMap);
                        deleteVectorOfPointers(connectionReaders);
                        unlock();
                        serverSocket->close();
                        future->cancel();
                    }

                    void JTransport::remove(JConnectionHeaderReader* reader){
                        lock();
                        deleteFromVector(connectionReaders, reader);
                        unlock();
                    }

                    void JTransport::remove(JConnections* connections){
                        remoteConnectionsMap->erase(connections->getRemoteEndPoint());
                    }

                    //TODO check which pattern is better, stopExport in delete constructor?
                    JTransport::~JTransport(){
                        deleteMapOfValuePointer(remoteConnectionsMap);
                        deleteVectorOfPointers(connectionReaders);
                    }
                }
            }
        }
    }
}


