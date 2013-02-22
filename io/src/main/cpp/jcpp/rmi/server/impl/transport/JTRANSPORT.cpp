#include "JTransport.h"
#include "JSystem.h"
#include "Collections.h"
#include "JConnectionHeaderReader.h"
#include "JGatewaySocketFactory.h"
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

                    JTransport::JTransport(JEndPoint* localEndPoint,JITransportRouter* transportRouter,JITransportDispatcher* transportDispatcher,JExecutorService* executorService,JScheduledExecutorService* scheduledExecutorService,JTransportConfiguration* transportConfiguration){
                        this->localEndPoint=localEndPoint;
                        this->transportRouter=transportRouter;
                        this->transportDispatcher=transportDispatcher;
                        this->scheduledExecutorService=scheduledExecutorService;
                        this->remoteConnectionsMap=new map<JEndPoint*,JConnections*,lessEndPoint>();
                        this->connectionReaders=new vector<JConnectionHeaderReader*>();
                        this->executorService=executorService;
                        this->transportConfiguration=transportConfiguration;
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

                    JTransportConfiguration* JTransport::getTransportConfiguration(){
                        return transportConfiguration;
                    }

                    void JTransport::startExport(){
                        serverSocket = JGatewaySocketFactory::createServerSocket(localEndPoint->getAddress()->getPHostName(),localEndPoint->getAddress()->getPPort(), transportConfiguration->getGatewayConfiguration());
                        serverSocket->connect();
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
                        serverSocket->close();
                        future->cancel();
                        lock();
                        for (unsigned int i=0;i<connectionReaders->size();i++){
                            JConnectionHeaderReader* reader=connectionReaders->at(i);
                            reader->unexport();
                        }
                        map<JEndPoint*,JConnections*>::iterator i;
                        for(i = remoteConnectionsMap->begin(); i != remoteConnectionsMap->end(); ++i){
                            JConnections* conns=(*i).second;
                            conns->killAll();
                        }
                        remoteConnectionsMap->clear();
                        connectionReaders->clear();
                        unlock();
                    }

                    void JTransport::remove(JConnectionHeaderReader* reader){
                        lock();
                        deleteFromVector(connectionReaders, reader);
                        unlock();
                    }

                    void JTransport::remove(JConnections* connections){
                        remoteConnectionsMap->erase(connections->getRemoteEndPoint());
                    }

                    JTransport::~JTransport(){
                        deleteMapOfValuePointer(remoteConnectionsMap);
                        deleteVectorOfPointers(connectionReaders);
                    }
                }
            }
        }
    }
}


