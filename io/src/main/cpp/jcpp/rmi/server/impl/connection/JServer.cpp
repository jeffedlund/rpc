#include "JServer.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JThreadPoolExecutor.h"
#include "JScheduledThreadPoolExecutor.h"
#include "JProxy.h"
#include "JObjectPointer.h"
#include "Collections.h"
#include "JInvoker.h"
using namespace jcpp::io;
using namespace jcpp::util::concurrent;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JServerClass : public JClass{
                      public:
                        JServerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.Server";
                            this->name="jcpp.rmi.server.impl.connection.Server";
                            this->simpleName="Server";
                            addInterface(JIGCClientListener::getClazz());
                            addInterface(JILifecycle::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JServer::getClazz(){
                        if (clazz==NULL){
                            clazz=new JServerClass();
                        }
                        return clazz;
                    }

                    JServer::JServer(JEndPoint* endPoint, JITransportRouter* transportRouter, JConnectionConfiguration* connectionConfiguration){
                        this->endPoint = endPoint;
                        this->connectionConfiguration = connectionConfiguration;
                        this->lifecycles = new vector<JILifecycle*>();
                        this->gcClientListeners = new vector<JIGCClientListener*>();
                        this->invocationListeners=new vector<JIInvocationListener*>();
                        this->executorService = new JThreadPoolExecutor(connectionConfiguration->getExecutorCorePoolSize()->get(),60000);//TODO
                        this->scheduledExecutorService = new JScheduledThreadPoolExecutor(connectionConfiguration->getExecutorCorePoolSize()->get(),60000);
                        this->gc = new JGC(executorService, scheduledExecutorService, connectionConfiguration);
                        this->gcClient = new JGCClient(this, this);
                        this->objectInformations = new JObjectInformations(this, this, gc, gcClient,this);
                        this->connectionTransportDispatcher = new JConnectionTransportDispatcher(objectInformations);
                        this->transport = new JTransport(endPoint, transportRouter, NULL/*connectionTransportDispatcher*/, executorService, scheduledExecutorService, connectionConfiguration->getTransportConfiguration());
                        this->objectInformations->setTransport(transport);
                        this->registry = new JRegistry(objectInformations);
                        vector<JClass*>* inter=new vector<JClass*>();
                        inter->push_back(JIRegistry::getClazz());
                        //TODO this->registry->bind(JIRegistry::getClazz()->getName(), registry, inter);
                        inter=new vector<JClass*>();
                        inter->push_back(JIServer::getClazz());
                        //TODO this->registry->bind(JIServer::getClazz()->getName(), this, inter);
                        inter=new vector<JClass*>();
                        inter->push_back(JIGC::getClazz());
                        //TODO this->registry->bind(JIGC::getClazz()->getName(), gc, inter);
                        inter=new vector<JClass*>();
                        inter->push_back(JIGCClient::getClazz());
                        //TODO this->registry->bind(JIGCClient::getClazz()->getName(), gcClient, inter);
                    }

                    JIServer* JServer::getRemoteServer(JObject* object){
                        if (object->getClass()->isProxy()){
                            JObjectHandler* objectHandler = getObjectHandlerFromProxy(object);
                            JObjectPointer* objectPointer = objectHandler->getInvoker()->getObjectPointer();
                            return (JIServer*)objectHandler->getInvoker()->getObjectInformations()->getServer()->lookup(objectPointer->getEndPoint(), JIServer::getClazz());
                        }
                        return NULL;
                    }

                    JIServer* JServer::getLocalServer(JObject* object){
                        JObjectHandler* objectHandler = getObjectHandlerFromProxy(object);
                        return objectHandler->getInvoker()->getObjectInformations()->getServer();
                    }

                    JString* JServer::getHost(JObject* object){
                        return getEndPoint(object)->getAddress()->getPHostName();
                    }

                    JPrimitiveInt* JServer::getPort(JObject* object){
                        return getEndPoint(object)->getAddress()->getPPort();
                    }

                    JString* JServer::getSite(JObject* object){
                        return getEndPoint(object)->getSite();
                    }

                    JEndPoint* JServer::getEndPoint(JObject* object){
                        if (object->getClass()->isProxy()) {
                            JObjectPointer* objectPointer = getObjectHandlerFromProxy(object)->getInvoker()->getObjectPointer();
                            return objectPointer->getEndPoint();
                        }
                        return NULL;
                    }

                    JString* JServer::getId(JObject* object){
                        if (object->getClass()->isProxy()) {
                            JObjectPointer* objectPointer = getObjectHandlerFromProxy(object)->getInvoker()->getObjectPointer();
                            return objectPointer->getId();
                        }
                        return NULL;
                    }

                    JObject* JServer::lookup(JEndPoint* endPoint, JClass* clazz){
                        vector<JClass*>* inter=new vector<JClass*>();
                        inter->push_back(clazz);
                        return NULL;//TODO lookup(clazz->getName(),endPoint,inter);
                    }

                    JObject* JServer::lookup(JString* id, JEndPoint* endPoint, vector<JClass*>* interfaces){
                        JObjectHandler* objectHandler = new JObjectHandler(objectInformations, interfaces, new JObjectPointer(endPoint, id));
                        return objectHandler->getProxy();
                    }

                    JIRegistry* JServer::getRegistry(){
                        return registry;
                    }

                    JEndPoint* JServer::getEndPoint(){
                        return endPoint;
                    }

                    JIGC* JServer::getGC(){
                        return gc;
                    }

                    JIGCClient* JServer::getGCClient(){
                        return gcClient;
                    }

                    JExecutorService* JServer::getExecutorService(){
                        return executorService;
                    }

                    JScheduledExecutorService* JServer::getScheduledExecutorService(){
                        return scheduledExecutorService;
                    }

                    JObjectInformations* JServer::getObjectInformations(){
                        return objectInformations;
                    }

                    JConnectionTransportDispatcher* JServer::getConnectionTransportDispatcher(){
                        return connectionTransportDispatcher;
                    }

                    JConnectionConfiguration* JServer::getConnectionConfiguration(){
                        return connectionConfiguration;
                    }

                    JINotExportedObjectListener* JServer::getNotExportedObjectListener(){
                        return notExportedObjectListener;
                    }

                    void JServer::setNotExportedObjectListener(JINotExportedObjectListener* notExportedObjectListener){
                        this->notExportedObjectListener=notExportedObjectListener;
                    }

                    JINotSerializableObjectHandler* JServer::getNotSerializableObjectHandler(){
                        return notSerializableObjectHandler;
                    }

                    void JServer::setNotSerializableObjectHandler(JINotSerializableObjectHandler* notSerializableObjectHandler){
                        this->notSerializableObjectHandler=notSerializableObjectHandler;
                    }

                    JIInvocationExceptionHandler* JServer::getInvocationExceptionHandler(){
                        return invocationExceptionHandler;
                    }

                    void JServer::setInvocationExceptionHandler(JIInvocationExceptionHandler* i){
                        this->invocationExceptionHandler=i;
                    }

                    void JServer::unexport(){
                        gcClient->unexport();
                        gc->unexport();
                        objectInformations->unexport();
                        scheduledExecutorService->shutdown();
                        executorService->shutdown();
                    }

                    void JServer::addLifecycle(JILifecycle* lifecycle){
                        lifecycles->push_back(lifecycle);
                    }

                    void JServer::removeLifecycle(JILifecycle* lifecycle){
                        deleteFromVector(lifecycles,lifecycle);
                    }

                    void JServer::addGCClientListener(JIGCClientListener* gcClientListener){
                        gcClientListeners->push_back(gcClientListener);
                    }

                    void JServer::removeGCClientListener(JIGCClientListener* gcClientListener){
                        deleteFromVector(gcClientListeners,gcClientListener);
                    }

                    void JServer::addInvocationListener(JIInvocationListener* i){
                        invocationListeners->push_back(i);
                    }

                    void JServer::removeInvocationListener(JIInvocationListener* i){
                        deleteFromVector(invocationListeners,i);
                    }

                    JObjectHandler* JServer::getObjectHandlerFromProxy(JObject* object){
                        if (object->getClass()->isProxy()) {
                            JInvocationHandler* invocationHandler = ((JProxy*)object)->getInvocationHandler();
                            if (((JObject*)invocationHandler)->getClass()==JObjectHandler::getClazz()) {
                                JObjectHandler* objectHandler = (JObjectHandler*) invocationHandler;
                                return objectHandler;
                            }
                            throw new JException("The Proxy object: " + object->toString() + " is not an instance of ObjectHandler.");
                        }
                        throw new JException("The object: " + object->toString() + " is not of type Proxy.");
                    }

                    void JServer::doExport(JObjectInformation* objectInformation, JEndPoint* endPoint){
                        for (unsigned int i=0;i<lifecycles->size();i++){
                            JILifecycle* l=lifecycles->at(i);
                            l->doExport(objectInformation,endPoint);
                        }
                    }

                    void JServer::unexport(JObjectInformation* objectInformation){
                        for (unsigned int i=0;i<lifecycles->size();i++){
                            JILifecycle* l=lifecycles->at(i);
                            l->unexport(objectInformation);
                        }
                    }

                    void JServer::doExport(JObjectInformation* objectInformation){
                        for (unsigned int i=0;i<lifecycles->size();i++){
                            JILifecycle* l=lifecycles->at(i);
                            l->doExport(objectInformation);
                        }
                    }

                    void JServer::unexport(JObjectInformation* objectInformation, JEndPoint* endPoint){
                        for (unsigned int i=0;i<lifecycles->size();i++){
                            JILifecycle* l=lifecycles->at(i);
                            l->unexport(objectInformation,endPoint);
                        }
                    }

                    void JServer::objectAlive(JEndPoint* endPoint, vector<JObject*>* objects){
                        for (unsigned int i=0;i<gcClientListeners->size();i++){
                            JIGCClientListener* l=gcClientListeners->at(i);
                            l->objectAlive(endPoint,objects);
                        }
                    }

                    void JServer::objectDead(JEndPoint* endPoint, vector<JObject*>* objects){
                        for (unsigned int i=0;i<gcClientListeners->size();i++){
                            JIGCClientListener* l=gcClientListeners->at(i);
                            l->objectDead(endPoint,objects);
                        }
                    }

                    void JServer::objectDead(JEndPoint* endPoint, vector<JObject*>* objects, JThrowable* throwable){
                        for (unsigned int i=0;i<gcClientListeners->size();i++){
                            JIGCClientListener* l=gcClientListeners->at(i);
                            l->objectDead(endPoint,objects,throwable);
                        }
                    }

                    void JServer::objectMaybeDead(JEndPoint* endPoint, vector<JObject*>* objects, JThrowable* throwable){
                        for (unsigned int i=0;i<gcClientListeners->size();i++){
                            JIGCClientListener* l=gcClientListeners->at(i);
                            l->objectMaybeDead(endPoint,objects,throwable);
                        }
                    }

                    void JServer::invocationSucceeded(JObject* proxy, JMethod* method, vector<JObject*>* args){
                        for (unsigned int i=0;i<invocationListeners->size();i++){
                            JIInvocationListener* l=invocationListeners->at(i);
                            l->invocationSucceeded(proxy,method,args);
                        }
                    }

                    void JServer::invocationFailed(JObject* proxy, JMethod* method, vector<JObject*>* args, JThrowable* e){
                        for (unsigned int i=0;i<invocationListeners->size();i++){
                            JIInvocationListener* l=invocationListeners->at(i);
                            l->invocationFailed(proxy,method,args,e);
                        }
                    }

                    string JServer::toString(){
                        return this->endPoint->toString();
                    }

                    JServer::~JServer(){
                        delete this->lifecycles;
                        delete this->gcClientListeners;
                        delete this->invocationListeners;
                        delete this->executorService;
                        delete this->scheduledExecutorService;
                        delete this->gc;
                        delete this->gcClient;
                        delete this->objectInformations;
                        delete this->connectionTransportDispatcher;
                        delete this->transport;
                        delete this->registry;
                    }
                }
            }
        }
    }
}


