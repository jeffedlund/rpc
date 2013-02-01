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
        this->bIsPrimitive=true;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JPrimitiveInt(0);
    }
};

static JClass* clazz;

JClass* JPrimitiveInt::getClazz(){
    if (clazz==NULL){
        clazz=new JPrimitiveIntClass();
    }
    return clazz;
}

JPrimitiveInt::JPrimitiveInt(qint32 value):JObject(getClazz()){
    this->value=value;
}

JPrimitiveInt::JPrimitiveInt():JObject(getClazz()){
    this->value=0;
}

void JPrimitiveInt::set(qint32 value){
    this->value=value;
}

qint32 JPrimitiveInt::get(){
    return value;
}

string JPrimitiveInt::toString(){
    stringstream sstr;
    sstr<<value;
    return sstr.str();
}

JPrimitiveInt::~JPrimitiveInt(){
}
