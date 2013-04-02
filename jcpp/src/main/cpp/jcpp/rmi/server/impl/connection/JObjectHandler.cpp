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
                      public:
                        JObjectHandlerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ObjectHandler";
                            this->name="jcpp.rmi.server.impl.connection.ObjectHandler";
                            this->simpleName="ObjectHandler";
                            addInterface(JSerializable::getClazz());
                            addInterface(JInvocationHandler::getClazz());
                            addInterface(JCloneable::getClazz());
                            serialVersionUID=3179670252394270616ULL;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
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
                        this->proxy = JProxy::newProxyInstance(interfaces, this);
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

                    //TODO what to do for Object methods (toString, equals, hashcode,...)
                    JObject* JObjectHandler::invoke(JObject* proxy, JMethod* method, vector<JObject*>* args){
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



