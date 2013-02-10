#include "JString.h"
#include "JClass.h"
#include "JSerializable.h"

class JStringClass : public JClass{
public:
  JStringClass(){
      this->canonicalName="java.lang.String";
      this->name="java.lang.String";
      this->simpleName="String";
      this->serialVersionUID=-6849794470754667710ULL;
      addInterface(JSerializable::getClazz());
  }

  JClass* getSuperclass(){
      return JObject::getClazz();
  }

  JObject* newInstance(){
      return new JString();
  }
};

static JClass* clazz;

JClass* JString::getClazz(){
    if (clazz==NULL){
        clazz=new JStringClass();
    }
    return clazz;
}

JString::JString(): JObject(getClazz()){
}

JString::JString(string str): JObject(getClazz()){
    this->str=str;
}

bool JString::operator==(JString &other){
    return (str==other.str);
}

JString::~JString() {
}

string JString::getString(){
    return str;
}

void JString::setString(string str) {
    this->str = str;
}

string JString::toString(){
    return str;
}
