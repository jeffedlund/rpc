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
        this->superClass=JObject::clazz;
    }
};

JClass* JBoolean::clazz=new JBooleanClass();

JBoolean::JBoolean(bool value):JObject(clazz){
    this->value=value;
}

void JBoolean::set(bool value){
    this->value=value;
}

bool JBoolean::get(){
    return value;
}

qint64 JBoolean::getSerialVersionUID(){
    return 1;
}

string JBoolean::toString(){
    return "[Boolean:"+(this->value?string("true]"):string("false]"));
}

JBoolean::~JBoolean(){
}

