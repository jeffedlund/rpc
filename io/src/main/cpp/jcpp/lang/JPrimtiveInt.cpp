#include "JPrimitiveInt.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class JPrimitiveIntClass : public JClass{
  public:
    JPrimitiveIntClass(){
        this->canonicalName="int";
        this->name="int";
        this->simpleName="int";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveInt::clazz=new JPrimitiveIntClass();

JPrimitiveInt::JPrimitiveInt(qint32 value):JObject(clazz){
    this->value=value;
}

void JPrimitiveInt::set(qint32 value){
    this->value=value;
}

qint32 JPrimitiveInt::get(){
    return value;
}

qint64 JPrimitiveInt::getSerialVersionUID(){
    return 1;
}

string JPrimitiveInt::toString(){
    stringstream sstr;
    sstr<<"[PrimitiveInt:"<<value<<"]";
    return sstr.str();
}

JPrimitiveInt::~JPrimitiveInt(){
}
