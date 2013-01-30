#include "JString.h"
#include "JClass.h"

class JStringClass : public JClass{
};

JString::JString(): JObject(clazz){
}

JClass* JString::clazz=new JStringClass();

JString::~JString() {
}

string JString::getString(){
    return str;
}

void JString::setString(string str) {
    this->str = str;
}
