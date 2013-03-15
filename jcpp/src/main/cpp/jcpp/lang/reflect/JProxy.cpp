#include "JProxy.h"
#include "JObject.h"
#include "JClass.h"
#include "JNoSuchMethodException.h"
#include <vector>
#include <string>
#include "Collections.h"
#include <sstream>
using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang::reflect;

//TODO think about how to detect a proxy in a serialized CPP object ...
namespace jcpp{
    namespace lang{
        namespace reflect{
            static JObject* staticGetInvocationHandler(JObject* obj){
                JProxy* proxy=(JProxy*)obj;
                return (JObject*)proxy->getInvocationHandler();
            }

            static void staticSetInvocationHandler(JObject* obj,JObject* value){
                JProxy* proxy=(JProxy*)obj;
                proxy->setInvocationHandler((JInvocationHandler*)value);
            }

            JProxy::JProxyClass::JProxyClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.reflect.Proxy";
                name="java.lang.reflect.Proxy";
                simpleName="Proxy";
                bIsProxy=true;
                serialVersionUID=-2222568056686623797ULL;
                addField(new JField("h",JInvocationHandler::getClazz(),staticGetInvocationHandler,staticSetInvocationHandler));
                addInterface(JSerializable::getClazz());
            }

            JClass* JProxy::JProxyClass::getSuperclass(){
                return JObject::getClazz();
            }

            JObject* JProxy::JProxyClass::newInstance(){
                return new JProxy();
            }

            static JClass* clazz;

            JClass* JProxy::getClazz(){
                if (clazz==NULL){
                    clazz=new JProxyClass();
                }
                return clazz;
            }

            JProxy::JProxy(JClass* _class):JObject(_class){
            }

            JProxy::JProxy():JObject(getClazz()){
                this->interfaces=NULL;
                this->invocationHandler=NULL;
            }

            JProxy::JProxy(vector<JClass*>* interfaces, JInvocationHandler* i):JObject(getClazz()){
                this->interfaces=interfaces;
                this->invocationHandler=i;
            }

            JProxy* JProxy::create(vector<JClass*>* interfaces, JInvocationHandler* ih){
                JProxy* proxy=NULL;
                for (unsigned int i=0;i<interfaces->size();i++){
                    JClass* ci=interfaces->at(i);
                    try{
                        JClass* c=ci->getClassLoader()->loadClass(ci->getName()+"Proxy");//maybe define getProxyClass in interfaces ...
                        if (JProxy::getClazz()->isAssignableFrom(c)){
                            proxy=(JProxy*)c->newInstance();
                            proxy->setInterfaces(interfaces);
                            proxy->setInvocationHandler(ih);
                            break;
                        }
                    }catch(JThrowable* th){
                    }
                }
                if (proxy==NULL){
                    proxy=new JProxy(interfaces,ih);
                }
                return proxy;
            }

            JObject* JProxy::invoke(string method,vector<JObject*>* args){
                JMethod* jMethod=NULL;
                for (unsigned int i=0;i<interfaces->size();i++){
                    JClass* jclass=interfaces->at(i);
                    if (jclass->hasMethod(method,NULL)){//should pass paramtype too
                        jMethod=jclass->getMethod(method,NULL);
                        break;
                    }
                }
                if (jMethod==NULL){
                    throw JNoSuchMethodException("method "+method+" not declared in "+toString());
                }
                return invocationHandler->invoke(this,jMethod,args);
            }

            JInvocationHandler* JProxy::getInvocationHandler(){
                return invocationHandler;
            }

            void JProxy::setInvocationHandler(JInvocationHandler* invocationHandler) {
                delete this->invocationHandler;
                this->invocationHandler = invocationHandler;
            }

            vector<JClass*>* JProxy::getInterfaces(){
                return interfaces;
            }

            void JProxy::setInterfaces(vector<JClass*>* interfaces){
                delete this->interfaces;
                this->interfaces=interfaces;
            }

            string JProxy::toString(){
                stringstream ss;
                ss<<"Proxy[InvocationHandler:"<<((JObject*)invocationHandler)->toString()<<"][Interfaces:";
                for (unsigned int i=0;i<interfaces->size();i++){
                    JClass* jclass=interfaces->at(i);
                    ss<<jclass->getName()<<",";
                }
                ss<<"]";
                return ss.str();
            }

            JProxy::~JProxy() {
                delete interfaces;
            }
        }
    }
}
