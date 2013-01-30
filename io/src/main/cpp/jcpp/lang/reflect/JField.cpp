#include "JField.h"
#include "JClass.h"

class JFieldClass : public JClass{
};

JClass* JField::clazz = new JFieldClass();

JField::JField(std::string name,JClass* type):JObject(clazz){
    this->name=name;
    this->type=type;
}

std::string JField::getName(){
    return name;
}

JClass* JField::getType(){
    return type;
}

JObject* get(JObject* object){
    return NULL;//TODO
}

void set(JObject* object, JObject *value){
    //TODO
}

std::string JField::toString(){
    return "JField";//TODO
}
