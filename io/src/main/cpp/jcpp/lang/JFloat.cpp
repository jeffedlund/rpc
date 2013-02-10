#include "JFloat.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class JFloatClass : public JClass{
  public:
    JFloatClass(){
        this->canonicalName="java.lang.Float";
        this->name="java.lang.Float";
        this->simpleName="Float";
        this->serialVersionUID=-2671257302660747028ULL;
    }

    JClass* getSuperclass(){
        return JNumber::getClazz();
    }

    JObject* newInstance(){
        return new JFloat(0);
    }
};

static JClass* clazz;

JClass* JFloat::getClazz(){
    if (clazz==NULL){
        clazz=new JFloatClass();
    }
    return clazz;
}

JFloat::JFloat(float value):JNumber(getClazz()){
    this->value=value;
}

JFloat::JFloat():JNumber(getClazz()){
    this->value=0;
}

void JFloat::set(float value){
    this->value=value;
}

float JFloat::get(){
    return value;
}

string JFloat::toString(){
    stringstream ss;
    ss<<value;
    return ss.str();
}

JFloat::~JFloat(){
}
