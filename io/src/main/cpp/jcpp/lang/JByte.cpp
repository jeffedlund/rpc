#include "JByte.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JByteClass : public JClass{
  public:
    JByteClass(){
        this->canonicalName="java.lang.Byte";
        this->name="java.lang.Byte";
        this->simpleName="Byte";
        this->superClass=JObject::clazz;
    }
};

JClass* JByte::clazz=new JByteClass();

JByte::JByte(qint8 value):JObject(clazz){
    this->value=value;
}

void JByte::set(qint8 value){
    this->value=value;
}

qint8 JByte::get(){
    return value;
}

qint64 JByte::getSerialVersionUID(){
    return 1;
}

string JByte::toString(){
    return "TODO";
}

JByte::~JByte(){
}
