#include "JObject.h"
#include "JClass.h"
#include "JClassLoader.h"

class JObjectClass : public JClass{
};

JClass* JObject::clazz=new JObjectClass();

JObject::JObject(){
}


JObject::JObject(JClass* _class){
    this->_class=_class;
}

JClass* JObject::getClass(){
    return this->_class;
}

qint64 JObject::getSerialVersionUID(){
    return 1;
}

std::string JObject::toString(){
    return "JObject";
}

JObject::~JObject(){
}
