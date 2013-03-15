#include "JObjectHandler.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
#include "JProxy.h"
#include "JInvoker.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JObjectHandlerClass : public JClass{
                        //TODO following should be serialized. invoker,proxy,interfaces;
                        //TODO do it while testing proxy
                      public:
                        JObjectHandlerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ObjectHandler";
                            this->name="jcpp.rmi.server.impl.connection.ObjectHandler";
                            this->simpleName="ObjectHandler";
                            addInterface(JSerializable::getClazz());
                            addInterface(JInvocationHandler::getClazz());
                            serialVersionUID=3179670252394270616ULL;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JObjectHandler::getClazz(){
                        if (clazz==NULL){
                            clazz=new JObjectHandlerClass();
                        }
                        return clazz;
                    }

                    JObjectHandler::JObjectHandler():JObject(getClazz()){
                        this->invoker=NULL;
                        this->proxy=NULL;
                        this->classLoader=NULL;
                        this->interfaces=NULL;
                        this->invocationListener=NULL;
                    }

                    JObjectHandler::JObjectHandler(JObjectInformations* objectInformations,vector<JClass*>* interfaces, JObjectPointer* objectPointer){
                        this->invoker = new JInvoker(objectInformations, objectPointer);
                        this->proxy = JProxy::create(interfaces, this);
                        this->interfaces = interfaces;
                        this->invocationListener = objectInformations->getInvocationListener();
                    }

                    JObject* JObjectHandler::getProxy(){
                        return proxy;
                    }

                    JInvoker* JObjectHandler::getInvoker(){
                        return invoker;
                    }

                    vector<JClass*>* JObjectHandler::getInterfaces(){
                        return interfaces;
                    }

                    JObject* JObjectHandler::invoke(JObject* proxy, JMethod* method, vector<JObject*>* args){//TODO what to do for Object methods (toString, equals, hashcode,...)
                        JObject* invocationResult = NULL;
                        try {
                            invocationResult = invoker->invoke(method, args);
                            invocationListener->invocationSucceeded(proxy, method, args);
                        } catch (JThrowable* e) {
                            invocationListener->invocationFailed(proxy, method, args, e);
                            throw e;
                        }
                        return invocationResult;
                    }

                    void JObjectHandler::setObjectInformations(JObjectInformations* objectInformations){
                        invoker->setObjectInformations(objectInformations);
                        invocationListener = objectInformations->getInvocationListener();
                    }

                    JObject* JObjectHandler::clone(){
                        JObjectHandler* objectHandler = new JObjectHandler(invoker->getObjectInformations(), interfaces, invoker->getObjectPointer());
                        return objectHandler;
                    }

                    JObjectHandler::~JObjectHandler(){
                        delete invoker;
                        delete proxy;
                    }
                }
            }
        }
    }
}



