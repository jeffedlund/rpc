#include "JMethod.h"
#include "JClass.h"
#include "JInstantiationException.h"

class JMethodClass : public JClass{
    public:
        JMethodClass():JClass(JClassLoader::getBootClassLoader()){
            canonicalName="java.lang.reflect.Method";
            name="java.lang.reflect.Method";
            simpleName="Method";
        }

        JClass* getSuperclass(){
            return JObject::getClazz();//TODO "java.lang.reflect.AccessibleObject";
        }

        JObject* newInstance(){
            throw new JInstantiationException("cannot instantiate object of class "+getName());
        }
};

static JClass* clazz;

JClass* JMethod::getClazz(){
    if (clazz==NULL){
        clazz= new JMethodClass();
    }
    return clazz;
}

JMethod::JMethod(std::string name,JClass* declaringClass,JClass* returnType):JObject(getClazz()){
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
