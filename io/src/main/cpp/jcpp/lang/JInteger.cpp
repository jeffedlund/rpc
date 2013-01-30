#include "JInteger.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JIntegerClass : public JClass{
  public:
    JIntegerClass(){
        this->canonicalName="java.lang.Integer";
        this->name="java.lang.Integer";
        this->simpleName="java.lang.Integer";
        this->superClass=JObject::clazz;
    }
};

JClass* JInteger::clazz=new JIntegerClass();

JInteger::JInteger(qint32 value):JObject(clazz){
    this->value=value;
}

void JInteger::set(qint32 value){
    this->value=value;
}

qint32 JInteger::get(){
    return value;
}

qint64 JInteger::getSerialVersionUID(){
    return 1;
}

string JInteger::toString(){
    return "TODO";
}

JInteger::~JInteger(){
}
