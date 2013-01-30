#include "JFloat.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JFloatClass : public JClass{
  public:
    JFloatClass(){
        this->canonicalName="java.lang.Float";
        this->name="java.lang.Float";
        this->simpleName="java.lang.Float";
        this->superClass=JObject::clazz;
    }
};

JClass* JFloat::clazz=new JFloatClass();

JFloat::JFloat(float value):JObject(clazz){
    this->value=value;
}

void JFloat::set(float value){
    this->value=value;
}

float JFloat::get(){
    return value;
}

qint64 JFloat::getSerialVersionUID(){
    return 1;
}

string JFloat::toString(){
    return "TODO";
}

JFloat::~JFloat(){
}
