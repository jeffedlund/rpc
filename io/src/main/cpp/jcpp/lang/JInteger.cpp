#include "JInteger.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class JIntegerClass : public JClass{
  public:
    JIntegerClass(){
        this->canonicalName="java.lang.Integer";
        this->name="java.lang.Integer";
        this->simpleName="Integer";
        this->serialVersionUID=1360826667806852920L;
    }

    JClass* getSuperclass(){
        return JNumber::getClazz();
    }

    JObject* newInstance(){
        return new JInteger(0);
    }
};

static JClass* clazz;

JClass* JInteger::getClazz(){
    if (clazz==NULL){
        clazz=new JIntegerClass();
    }
    return clazz;
}

JInteger::JInteger(qint32 value):JNumber(getClazz()){
    this->value=value;
}

JInteger::JInteger():JNumber(getClazz()){
    this->value=0;
}

void JInteger::set(qint32 value){
    this->value=value;
}

qint32 JInteger::get(){
    return value;
}

string JInteger::toString(){
    stringstream ss;
    ss<<value;
    return ss.str();
}

JInteger::~JInteger(){
}
