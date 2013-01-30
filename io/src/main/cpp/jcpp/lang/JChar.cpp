#include "JChar.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class JCharClass : public JClass{
  public:
    JCharClass(){
        this->canonicalName="java.lang.Character";
        this->name="java.lang.Character";
        this->simpleName="Character";
        this->superClass=JObject::clazz;
    }
};

JClass* JChar::clazz=new JCharClass();

JChar::JChar(char value):JObject(clazz){
    this->value=value;
}

void JChar::set(char value){
    this->value=value;
}

char JChar::get(){
    return value;
}

qint64 JChar::getSerialVersionUID(){
    return 1;
}

string JChar::toString(){
    return "[Char:"+string(&value)+"]";
}

JChar::~JChar(){
}
