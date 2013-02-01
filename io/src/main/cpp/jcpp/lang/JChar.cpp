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
        this->serialVersionUID=3786198910865385080L;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JChar(0);
    }
};

static JClass* clazz;

JClass* JChar::getClazz(){
    if (clazz==NULL){
        clazz=new JCharClass();
    }
    return clazz;
}

JChar::JChar(char value):JObject(getClazz()){
    this->value=value;
}

JChar::JChar():JObject(getClazz()){
    this->value=0;
}

void JChar::set(char value){
    this->value=value;
}

char JChar::get(){
    return value;
}

string JChar::toString(){
    return ""+value;
}

JChar::~JChar(){
}
