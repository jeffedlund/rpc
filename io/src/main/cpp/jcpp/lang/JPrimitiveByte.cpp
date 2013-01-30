#include "JPrimitiveByte.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JPrimitiveByteClass : public JClass{
  public:
    JPrimitiveByteClass(){
        this->canonicalName="byte";
        this->name="byte";
        this->simpleName="byte";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveByte::clazz=new JPrimitiveByteClass();

JPrimitiveByte::JPrimitiveByte(qint8 value):JObject(clazz){
    this->value=value;
}

void JPrimitiveByte::set(qint8 value){
    this->value=value;
}

qint8 JPrimitiveByte::get(){
    return value;
}

qint64 JPrimitiveByte::getSerialVersionUID(){
    return 1;
}

string JPrimitiveByte::toString(){
    return "TODO";
    //TODO return "[PrimitiveByte:"+value+"]";
}

JPrimitiveByte::~JPrimitiveByte(){
}
