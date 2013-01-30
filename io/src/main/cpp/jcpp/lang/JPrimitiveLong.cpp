#include "JPrimitiveLong.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JPrimitiveLongClass : public JClass{
  public:
    JPrimitiveLongClass(){
        this->canonicalName="long";
        this->name="long";
        this->simpleName="long";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveLong::clazz=new JPrimitiveLongClass();

JPrimitiveLong::JPrimitiveLong(qint64 value):JObject(clazz){
    this->value=value;
}

void JPrimitiveLong::set(qint64 value){
    this->value=value;
}

qint64 JPrimitiveLong::get(){
    return value;
}

qint64 JPrimitiveLong::getSerialVersionUID(){
    return 1;
}

string JPrimitiveLong::toString(){
    return "[PrimitiveLong:";//TODO +value+"]";
}

JPrimitiveLong::~JPrimitiveLong(){
}
