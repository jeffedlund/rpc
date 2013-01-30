#include "JPrimitiveShort.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JPrimitiveShortClass : public JClass{
  public:
    JPrimitiveShortClass(){
        this->canonicalName="short";
        this->name="short";
        this->simpleName="short";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveShort::clazz=new JPrimitiveShortClass();

JPrimitiveShort::JPrimitiveShort(qint16 value):JObject(clazz){
    this->value=value;
}

void JPrimitiveShort::set(qint16 value){
    this->value=value;
}

qint16 JPrimitiveShort::get(){
    return value;
}

qint64 JPrimitiveShort::getSerialVersionUID(){
    return 1;
}

string JPrimitiveShort::toString(){
    return "[PrimitiveShort:";//TODO +value+"]";
}

JPrimitiveShort::~JPrimitiveShort(){
}
