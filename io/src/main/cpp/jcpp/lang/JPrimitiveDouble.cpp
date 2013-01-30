#include "JPrimitiveDouble.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JPrimitiveDoubleClass : public JClass{
  public:
    JPrimitiveDoubleClass(){
        this->canonicalName="double";
        this->name="double";
        this->simpleName="double";
        this->superClass=JObject::clazz;
        this->bIsPrimitive=true;
    }
};

JClass* JPrimitiveDouble::clazz=new JPrimitiveDoubleClass();

JPrimitiveDouble::JPrimitiveDouble(double value):JObject(clazz){
    this->value=value;
}

void JPrimitiveDouble::set(double value){
    this->value=value;
}

double JPrimitiveDouble::get(){
    return value;
}

qint64 JPrimitiveDouble::getSerialVersionUID(){
    return 1;
}

string JPrimitiveDouble::toString(){
    return "[PrimitiveDouble:";//TODO +value+"]";
}

JPrimitiveDouble::~JPrimitiveDouble(){
}

