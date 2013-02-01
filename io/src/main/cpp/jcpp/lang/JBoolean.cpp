#include "JBoolean.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JBooleanClass : public JClass{
  public:
    JBooleanClass(){
        this->canonicalName="java.lang.Boolean";
        this->name="java.lang.Boolean";
        this->simpleName="Boolean";
        this->serialVersionUID=-3665804199014368530L;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JBoolean(false);
    }
};

static JClass* clazz;

JClass* JBoolean::getClazz(){
    if (clazz==NULL){
        clazz=new JBooleanClass();
    }
    return clazz;
}

JBoolean::JBoolean(bool value):JObject(getClazz()){
    this->value=value;
}

JBoolean::JBoolean():JObject(getClazz()){
    this->value=false;
}

void JBoolean::set(bool value){
    this->value=value;
}

bool JBoolean::get(){
    return value;
}

string JBoolean::toString(){
    return (this->value?"true":"false");
}

JBoolean::~JBoolean(){
}

