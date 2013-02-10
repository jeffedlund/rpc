#include "JDouble.h"
#include "JNumber.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class JDoubleClass : public JClass{
  public:
    JDoubleClass(){
        this->canonicalName="java.lang.Double";
        this->name="java.lang.Double";
        this->simpleName="Double";
        this->serialVersionUID=-9172774392245257468ULL;
    }

    JClass* getSuperclass(){
        return JNumber::getClazz();
    }

    JObject* newInstance(){
        return new JDouble(0);
    }
};

static JClass* clazz;

JClass* JDouble::getClazz(){
    if (clazz==NULL){
        clazz=new JDoubleClass();
    }
    return clazz;
}

JDouble::JDouble(double value):JNumber(JDouble::getClazz()){
    this->value=value;
}

JDouble::JDouble():JNumber(JDouble::getClazz()){
    this->value=0;
}

void JDouble::set(double value){
    this->value=value;
}

double JDouble::get(){
    return value;
}

string JDouble::toString(){
    stringstream ss;
    ss<<value;
    return ss.str();
}

JDouble::~JDouble(){
}
