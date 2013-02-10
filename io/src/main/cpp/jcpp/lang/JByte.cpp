#include "JByte.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JByteClass : public JClass{
  public:
    JByteClass():JClass(){
        this->canonicalName="java.lang.Byte";
        this->name="java.lang.Byte";
        this->simpleName="Byte";
        this->serialVersionUID=-7183698231559129828ULL;
    }

    JClass* getSuperclass(){
        return JNumber::getClazz();
    }

    JObject* newInstance(){
        return new JByte(0);
    }
};

static JClass* clazz;

JClass* JByte::getClazz(){
    if (clazz==NULL){
        clazz=new JByteClass();
    }
    return clazz;
}

JByte::JByte(qint8 value):JNumber(getClazz()){
    this->value=value;
}

JByte::JByte():JNumber(getClazz()){
    this->value=0;
}

void JByte::set(qint8 value){
    this->value=value;
}

qint8 JByte::get(){
    return value;
}

string JByte::toString(){
    return ""+value;
}

JByte::~JByte(){
}
