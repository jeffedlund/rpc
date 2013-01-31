#include "JString.h"
#include "JClass.h"

class JStringClass : public JClass{
public:
  JStringClass(){
      this->canonicalName="java.lang.String";
      this->name="java.lang.String";
      this->simpleName="String";
      this->superClass=JObject::clazz;
  }
};

JString::JString(): JObject(clazz){
}

JString::JString(string str): JObject(clazz){
    this->str=str;
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
