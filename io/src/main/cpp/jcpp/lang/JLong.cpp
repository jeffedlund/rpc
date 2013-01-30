#include "JLong.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JLongClass : public JClass{
  public:
    JLongClass(){
        this->canonicalName="java.lang.Long";
        this->name="java.lang.Long";
        this->simpleName="Long";
        this->superClass=JObject::clazz;
    }
};

JClass* JLong::clazz=new JLongClass();

JLong::JLong(qint64 value):JObject(clazz){
    this->value=value;
}

void JLong::set(qint64 value){
    this->value=value;
}

qint64 JLong::get(){
    return value;
}

qint64 JLong::getSerialVersionUID(){
    return 1;
}

string JLong::toString(){
    return "TODO";
}

JLong::~JLong(){
}
