#include "JMethod.h"
#include "JClass.h"

class JMethodClass : public JClass{
};

JClass* JMethod::clazz = new JMethodClass();

JMethod::JMethod(std::string name,JClass* declaringClass,JClass* returnType):JObject(clazz){
    this->name=name;
    this->declaringClass=declaringClass;
    this->returnType=returnType;
    this->parameterType=NULL;//TODO
}

std::string JMethod::getName(){
    return name;
}

JClass* JMethod::getDeclaringClass(){
    return declaringClass;
}

JClass* JMethod::getReturnType(){
    return returnType;
}

std::vector<JClass>* JMethod::getParameterType(){
    return parameterType;
}

JObject* JMethod::invoke(JObject* object, JObject *args[]){
    return NULL;
}

std::string JMethod::toString(){
    return "JMethod";
}
