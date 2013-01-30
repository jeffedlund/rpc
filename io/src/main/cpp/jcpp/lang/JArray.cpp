#include "JArray.h"
#include "JClass.h"

JArrayClass::JArrayClass(JClass* componentType){
  this->componentType=componentType;
  string cn=componentType->getCanonicalName();
  if (!cn.empty()){
      this->canonicalName=cn+"[]";
  }
  this->name="TODO";
  this->simpleName=componentType->getSimpleName()+"[]";
  this->superClass=JObject::clazz;
  this->bIsArray=true;
}

JArray::JArray(JArrayClass* arrayClass):JObject(arrayClass){
    objects=new vector<JObject*>;
}

JArray::~JArray(){
}
