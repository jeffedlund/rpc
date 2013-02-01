#include "JProxy.h"
#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <string>

class JProxyClass : public JClass{
public:
    JProxyClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.reflect.Proxy";
        name="java.lang.reflect.Proxy";
        simpleName="Proxy";
        serialVersionUID=-2222568056686623797L;
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

JProxy::JProxy():JObject(getClazz()){}

JObject* invoke(){return NULL;}

JInvocationHandler* JProxy::getInvocationHandler(){
    return invocationHandler;
}

void JProxy::setInvocationHandler(JInvocationHandler* invocationHandler) {
    this->invocationHandler = invocationHandler;
}

bool JProxy::isProxy(){
    return true;
}

std::vector<std::string>* JProxy::getInterfaces(){//TODO
    std::vector<std::string>* v=new std::vector<std::string>();
    v->clear();
    return v;
}

JProxy::~JProxy() {
}
