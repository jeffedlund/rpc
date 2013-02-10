#include "JProxy.h"
#include "JObject.h"
#include "JClass.h"
#include "JNoSuchMethodException.h"
#include <vector>
#include <string>
#include "Collections.h"
#include <sstream>

class JProxyClass : public JClass{
public:
    JProxyClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.reflect.Proxy";
        name="java.lang.reflect.Proxy";
        simpleName="Proxy";
        bIsProxy=true;
        serialVersionUID=-2222568056686623797ULL;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JProxy();
    }
};

static JClass* clazz;

JClass* JProxy::getClazz(){
    if (clazz==NULL){
        clazz=new JProxyClass();
    }
    return clazz;
}

JProxy::JProxy():JObject(getClazz()){
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
    this->invocationHandler = invocationHandler;
}

vector<JClass*>* JProxy::getInterfaces(){
    return interfaces;
}

void JProxy::setInterfaces(vector<JClass*>* interfaces){
    this->interfaces=interfaces;
}

string JProxy::toString(){
    stringstream ss;
    ss<<"Proxy[InvocationHandler:"<<invocationHandler->toString()<<"][Interfaces:";
    for (unsigned int i=0;i<interfaces->size();i++){
        JClass* jclass=interfaces->at(i);
        ss<<jclass->getName()<<",";
    }
    ss<<"]";
    return ss.str();
}

JProxy::~JProxy() {
    if (interfaces!=NULL){
        deleteVectorOfPointers(interfaces);
    }
}
