#include "JProxy.h"
#include "JObject.h"
#include "JClass.h"
#include "JNoSuchMethodException.h"
#include <vector>
#include "Collections.h"
#include <sstream>
#include "JNullPointerException.h"
#include "JIllegalArgumentException.h"
#include "JClassLoader.h"
using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
            static JObject* staticGetInvocationHandler(JObject* obj){
                JProxy* proxy=(JProxy*)obj;
                return dynamic_cast<JObject*>(proxy->getInvocationHandler());
            }

            static void staticSetInvocationHandler(JObject* obj,JObject* value){
                JProxy* proxy=(JProxy*)obj;
                proxy->setInvocationHandler(dynamic_cast<JInvocationHandler*>(value));
            }

            JProxy::JProxyClass::JProxyClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.reflect.Proxy";
                name="java.lang.reflect.Proxy";
                simpleName="Proxy";
                serialVersionUID=-2222568056686623797ULL;
                addField(new JField("h",JInvocationHandler::getClazz(),this,staticGetInvocationHandler,staticSetInvocationHandler));
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
                this->invocationHandler=NULL;
            }

            JProxy::JProxy():JObject(getClazz()){
                this->invocationHandler=NULL;
            }

            JProxy::JProxy(JInvocationHandler* i):JObject(getClazz()){
                this->invocationHandler=i;
            }

            JClass* JProxy::getProxyClass(vector<JClass*>* interfaces){
                JClass* pc=NULL;
                for (unsigned int i=0;i<interfaces->size();i++){
                    JClass* ci=interfaces->at(i);
                    try{
                        JClass* c=ci->getClassLoader()->loadClass(ci->getName()+"Proxy");//maybe define getProxyClass in interfaces ...
                        if (JProxy::getClazz()->isAssignableFrom(c)){
                            pc=c;
                            break;
                        }
                    }catch(JThrowable* th){
                    }
                }
                return pc;
            }

            JProxy* JProxy::newProxyInstance(vector<JClass*>* interfaces, JInvocationHandler* ih){
                JProxy* proxy=NULL;
                JClass* pc=getProxyClass(interfaces);
                if (pc!=NULL){
                    proxy=(JProxy*)pc->newInstance();
                    proxy->setInvocationHandler(ih);
                }
                if (proxy==NULL){
                    proxy=new JProxy(ih);
                }
                return proxy;
            }

            jbool JProxy::isProxyClass(JClass* cl){
                if (cl==NULL){
                    throw new JNullPointerException();
                }
                return cl->isProxy();
            }

            JInvocationHandler* JProxy::getInvocationHandler(JObject* proxy){
                if (!proxy->getClass()->isProxy()){
                    throw new JIllegalArgumentException("not a proxy instance");
                }
                JProxy* p=dynamic_cast<JProxy*>(proxy);
                return p->getInvocationHandler();
            }

            JObject* JProxy::invoke(JString method,vector<JObject*>* args){
                JMethod* jMethod=NULL;
                for (unsigned int i=0;i<getClass()->getInterfaces()->size();i++){
                    JClass* jclass=getClass()->getInterfaces()->at(i);
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

            jint JProxy::hashCode(){
                JObject* myh=dynamic_cast<JObject*>(invocationHandler);
                return myh->hashCode();
            }

            jbool JProxy::equals(JObject *o){
                if (o->getClass()!=getClass()){
                    return false;
                }
                JProxy* p=(JProxy*)o;
                JObject* myh=dynamic_cast<JObject*>(invocationHandler);
                JObject* oyh=dynamic_cast<JObject*>(p->invocationHandler);
                return myh->equals(oyh);
            }

            JString JProxy::toString(){
                JString ss;
                JObject* o=dynamic_cast<JObject*>(invocationHandler);
                ss<<"Proxy[InvocationHandler:"<<o->toString()<<"][Interfaces:";
                for (unsigned int i=0;i<getClass()->getInterfaces()->size();i++){
                    JClass* jclass=getClass()->getInterfaces()->at(i);
                    ss<<jclass->getName()<<",";
                }
                ss<<"]";
                return ss;
            }

            JProxy::~JProxy() {
            }
        }
    }
}
