#include "JPrimitiveBoolean.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JPrimitiveBooleanClass : public JClass{
  public:
    JPrimitiveBooleanClass(){
        this->canonicalName="boolean";
        this->name="boolean";
        this->simpleName="boolean";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveBoolean::clazz=new JPrimitiveBooleanClass();

JPrimitiveBoolean::JPrimitiveBoolean(bool value):JObject(clazz){
    this->value=value;
}

void JPrimitiveBoolean::set(bool value){
    this->value=value;
}

bool JPrimitiveBoolean::get(){
    return value;
}

qint64 JPrimitiveBoolean::getSerialVersionUID(){
    return 1;
}

string JPrimitiveBoolean::toString(){
    return "[PrimitiveBoolean:"+(this->value?string("true]"):string("false]"));
}

JPrimitiveBoolean::~JPrimitiveBoolean(){
}
