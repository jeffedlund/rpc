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

JField::JField(std::string name,JClass* type):JObject(getClazz()){
    this->name=name;
    this->type=type;
}

std::string JField::getName(){
    return name;
}

JClass* JField::getType(){
    return type;
}

JObject* JField::get(JObject* object){
    return NULL;//TODO
}

void JField::set(JObject* object, JObject *value){
    //TODO
}

std::string JField::toString(){
    return "JField";//TODO
}
