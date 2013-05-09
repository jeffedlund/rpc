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
                    protected:
                        static JObject* staticGetInvoker(JObject* object){
                            JObjectHandler* s=(JObjectHandler*)object;
                            return s->invoker;
                        }

                        static void staticSetInvoker(JObject* object,JObject* value){
                            JObjectHandler* s=(JObjectHandler*)object;
                            s->invoker=((JInvoker*)value);
                        }

                        static JObject* staticGetProxy(JObject* object){
                            JObjectHandler* s=(JObjectHandler*)object;
                            return s->proxy;
                        }

                        static void staticSetProxy(JObject* object,JObject* value){
                            JObjectHandler* s=(JObjectHandler*)object;
                            s->proxy=value;
                        }

                        static JObject* staticGetInterfaces(JObject* object){
                            JObjectHandler* s=(JObjectHandler*)object;
                            return s->pinterfaces;
                        }

                        static void staticSetInterfaces(JObject* object,JObject* value){
                            JObjectHandler* s=(JObjectHandler*)object;
                            if (s->pinterfaces!=NULL){
                                delete s->pinterfaces;
                            }
                            s->pinterfaces=(JPrimitiveArray*)value;
                        }

                    public:
                        JObjectHandlerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ObjectHandler";
                            this->name="jcpp.rmi.server.impl.connection.ObjectHandler";
                            this->simpleName="ObjectHandler";
                            addInterface(JSerializable::getClazz());
                            addInterface(JInvocationHandler::getClazz());
                            addInterface(JCloneable::getClazz());
                            serialVersionUID=3179670252394270616ULL;
                            addField(new JField("invoker",JInvoker::getClazz(),this,staticGetInvoker,staticSetInvoker));
                            addField(new JField("proxy",JObject::getClazz(),this,staticGetProxy,staticSetProxy));
                            addField(new JField("interfaces",JPrimitiveArray::getClazz(JClass::getClazz()),this,staticGetInterfaces,staticSetInterfaces));
                        }

                        virtual JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        virtual JObject* newInstance(){
                            return new JObjectHandler();
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
                        this->pinterfaces=NULL;
                        this->invocationListener=NULL;
                    }

                    JObjectHandler::JObjectHandler(JObjectInformations* objectInformations,vector<JClass*>* interfaces, JObjectPointer* objectPointer):JObject(getClazz()){
                        this->invoker = new JInvoker(objectInformations, objectPointer);
                        this->proxy = JProxy::newProxyInstance(interfaces, this);
                        this->pinterfaces = new JPrimitiveArray(JClass::getClazz(),(vector<JObject*>*)interfaces);
                        this->invocationListener = objectInformations->getInvocationListener();
                    }

                    JObject* JObjectHandler::getProxy(){
                        return proxy;
                    }

                    JInvoker* JObjectHandler::getInvoker(){
                        return invoker;
                    }

                    vector<JClass*>* JObjectHandler::getInterfaces(){
                        return (pinterfaces!=NULL? (vector<JClass*>*)(pinterfaces->getObjects()):NULL);
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

                    JString JObjectHandler::toString(){
                        JString strInterfaces = "";
                        strInterfaces <<"Proxy[" << invoker->getObjectPointer()->toString() << ", Interfaces[";
                        if (getInterfaces()!=NULL && getInterfaces()->size()>0){
                            for (unsigned int i = 0; i < (getInterfaces()->size() - 1); i++) {
                                JClass* c=getInterfaces()->at(i);
                                strInterfaces << c->getName() << ", ";
                            }
                            JClass* c=getInterfaces()->at(getInterfaces()->size()-1);
                            strInterfaces << c->getName();
                        }
                        strInterfaces<<"]]";
                        return strInterfaces;
                    }

                    jint JObjectHandler::hashCode(){
                        return invoker->getObjectPointer()->hashCode();
                    }

                    jbool JObjectHandler::equals(JObject *o){
                        if (o->getClass()->isProxy()){
                            JProxy* p=(JProxy*)o;
                            JInvocationHandler* invocationHandler = p->getInvocationHandler();
                            JObject* oih=dynamic_cast<JObject*>(invocationHandler);
                            if (oih->isInstanceOf(JObjectHandler::getClazz())){
                                JObjectHandler* objectHandler = (JObjectHandler*) oih;
                                JObjectPointer* objectPointer = objectHandler->getInvoker()->getObjectPointer();
                                return invoker->getObjectPointer()->equals(objectPointer);
                            }
                        }
                        return false;
                    }

                    JObject* JObjectHandler::clone(){
                        JObjectHandler* objectHandler = new JObjectHandler(invoker->getObjectInformations(), getInterfaces(), invoker->getObjectPointer());
                        return objectHandler;
                    }

                    JObjectHandler::~JObjectHandler(){
                        delete invoker;
                        delete proxy;
                        delete pinterfaces;
                    }
                }
            }
        }
    }
}
