#include "JShort.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JShortClass : public JClass{
  public:
    JShortClass(){
        this->canonicalName="java.lang.Short";
        this->name="java.lang.Short";
        this->simpleName="Short";
        this->superClass=JObject::clazz;
    }
};

JClass* JShort::clazz=new JShortClass();

JShort::JShort(qint16 value):JObject(clazz){
    this->value=value;
}

void JShort::set(qint16 value){
    this->value=value;
}

qint16 JShort::get(){
    return value;
}

qint64 JShort::getSerialVersionUID(){
    return 1;
}

string JShort::toString(){
    return "TODO";
}

JShort::~JShort(){
}
