#include "JMethod.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <sstream>

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

JMethod::JMethod(string name,JClass* declaringClass,JClass* returnType,vector<JClass*>* parameterType):JObject(getClazz()){
    this->name=name;
    this->declaringClass=declaringClass;
    this->returnType=returnType;
    this->parameterType=parameterType;
}

string JMethod::getName(){
    return name;
}

JClass* JMethod::getDeclaringClass(){
    return declaringClass;
}

JClass* JMethod::getReturnType(){
    return returnType;
}

vector<JClass*>* JMethod::getParameterType(){
    return parameterType;
}

string JMethod::toString(){
    stringstream ss;
    ss<<returnType->getName()<<" ";
    ss<<declaringClass<<"."<<name;
    if (parameterType!=NULL){
        ss<<"(";
        for (unsigned int i=0;i<parameterType->size();i++){
            JClass* param=parameterType->at(i);
            ss<<param->getName()+",";
        }
    }
    return ss.str();
}
