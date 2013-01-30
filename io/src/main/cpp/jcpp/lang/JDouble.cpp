#include "JDouble.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JDoubleClass : public JClass{
  public:
    JDoubleClass(){
        this->canonicalName="java.lang.Double";
        this->name="java.lang.Double";
        this->simpleName="java.lang.Double";
        this->superClass=JObject::clazz;
    }
};

JClass* JDouble::clazz=new JDoubleClass();

JDouble::JDouble(double value):JObject(clazz){
    this->value=value;
}

void JDouble::set(double value){
    this->value=value;
}

double JDouble::get(){
    return value;
}

qint64 JDouble::getSerialVersionUID(){
    return 1;
}

string JDouble::toString(){
    return "TODO";
}

JDouble::~JDouble(){
}
