#include "JShort.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class JShortClass : public JClass{
  public:
    JShortClass(){
        this->canonicalName="java.lang.Short";
        this->name="java.lang.Short";
        this->simpleName="Short";
        this->serialVersionUID=7515723908773894738L;
    }

    JClass* getSuperclass(){
        return JNumber::getClazz();
    }

    JObject* newInstance(){
        return new JShort(0);
    }
};

static JClass* clazz;

JClass* JShort::getClazz(){
    if (clazz==NULL){
        clazz=new JShortClass();
    }
    return clazz;
}

JShort::JShort(qint16 value):JNumber(getClazz()){
    this->value=value;
}

JShort::JShort():JNumber(getClazz()){
    this->value=0;
}

void JShort::set(qint16 value){
    this->value=value;
}

qint16 JShort::get(){
    return value;
}

string JShort::toString(){
    stringstream ss;
    ss<<value;
    return ss.str();
}

JShort::~JShort(){
}
