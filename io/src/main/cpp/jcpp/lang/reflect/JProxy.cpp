#include "JProxy.h"
#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <string>

class JProxyClass : public JClass{
};

JClass* JProxy::clazz=new JProxyClass();

JProxy::JProxy():JObject(clazz){}

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

std::vector<std::string>* JProxy::getInterfaces(){
    std::vector<std::string>* v=new std::vector<std::string>();
    v->clear();
    return v;
}

JProxy::~JProxy() {
}
