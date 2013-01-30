#include "JPrimitiveFloat.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JPrimitiveFloatClass : public JClass{
  public:
    JPrimitiveFloatClass(){
        this->canonicalName="float";
        this->name="float";
        this->simpleName="float";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveFloat::clazz=new JPrimitiveFloatClass();

JPrimitiveFloat::JPrimitiveFloat(float value):JObject(clazz){
    this->value=value;
}

void JPrimitiveFloat::set(float value){
    this->value=value;
}

float JPrimitiveFloat::get(){
    return value;
}

qint64 JPrimitiveFloat::getSerialVersionUID(){
    return 1;
}

string JPrimitiveFloat::toString(){
    return "[PrimitiveFloat:";//TODO +value+"]";
}

JPrimitiveFloat::~JPrimitiveFloat(){
}
