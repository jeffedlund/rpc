#include "JField.h"
#include "JClass.h"
#include "JInstantiationException.h"

class JFieldClass : public JClass{
public:
    JFieldClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.reflect.Field";
        name="java.lang.reflect.Field";
        simpleName="Field";
    }

    JClass* getSuperclass(){
        return JObject::getClazz();//TODO "java.lang.reflect.AccessibleObject";
    }

    JObject* newInstance(){
        throw new JInstantiationException("cannot instantiate object of class "+getName());
    }
};

static JClass* clazz;

JClass* JField::getClazz(){//TODO use mutex
    if (clazz==NULL){
        clazz= new JFieldClass();
    }
    return clazz;
}

JField::JField(string name,JClass* type):JObject(getClazz()){
    this->name=name;
    this->type=type;
}

string JField::getName(){
    return name;
}

JClass* JField::getType(){
    return type;
}

string JField::toString(){
    return getType()->getName()+"."+getName();
}
