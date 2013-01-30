#include "JPrimitiveChar.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JPrimitiveCharClass : public JClass{
  public:
    JPrimitiveCharClass(){
        this->canonicalName="char";
        this->name="char";
        this->simpleName="char";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveChar::clazz=new JPrimitiveCharClass();

JPrimitiveChar::JPrimitiveChar(char value):JObject(clazz){
    this->value=value;
}

void JPrimitiveChar::set(char value){
    this->value=value;
}

char JPrimitiveChar::get(){
    return value;
}

qint64 JPrimitiveChar::getSerialVersionUID(){
    return 1;
}

string JPrimitiveChar::toString(){
    return "[PrimitiveChar:"+string(&value)+"]";
}

JPrimitiveChar::~JPrimitiveChar(){
}

