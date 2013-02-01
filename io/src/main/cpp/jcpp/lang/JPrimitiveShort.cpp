#include "JPrimitiveShort.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class JPrimitiveShortClass : public JClass{
  public:
    JPrimitiveShortClass(){
        this->canonicalName="short";
        this->name="short";
        this->simpleName="short";
        this->bIsPrimitive=true;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JPrimitiveShort(0);
    }
};

static JClass* clazz;

JClass* JPrimitiveShort::getClazz(){
    if (clazz==NULL){
        clazz=new JPrimitiveShortClass();
    }
    return clazz;
}

JPrimitiveShort::JPrimitiveShort(qint16 value):JObject(getClazz()){
    this->value=value;
}

JPrimitiveShort::JPrimitiveShort():JObject(getClazz()){
    this->value=0;
}

void JPrimitiveShort::set(qint16 value){
    this->value=value;
}

qint16 JPrimitiveShort::get(){
    return value;
}

string JPrimitiveShort::toString(){
    stringstream ss;
    ss<<value;
    return ss.str();
}

JPrimitiveShort::~JPrimitiveShort(){
}
