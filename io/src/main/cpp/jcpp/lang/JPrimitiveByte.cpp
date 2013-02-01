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
        this->bIsPrimitive=true;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JPrimitiveByte(0);
    }
};

static JClass* clazz;

JClass* JPrimitiveByte::getClazz(){
    if (clazz==NULL){
        clazz=new JPrimitiveByteClass();
    }
    return clazz;
}

JPrimitiveByte::JPrimitiveByte(qint8 value):JObject(getClazz()){
    this->value=value;
}

JPrimitiveByte::JPrimitiveByte():JObject(getClazz()){
    this->value=0;
}

void JPrimitiveByte::set(qint8 value){
    this->value=value;
}

qint8 JPrimitiveByte::get(){
    return value;
}

string JPrimitiveByte::toString(){
    return ""+value;
}

JPrimitiveByte::~JPrimitiveByte(){
}
