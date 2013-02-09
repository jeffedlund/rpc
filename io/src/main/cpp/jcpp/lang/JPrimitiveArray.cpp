#include "JPrimitiveArray.h"
#include "JClass.h"
#include "Collections.h"
#include <map>
#include <vector>
#include "JSerializable.h"
using namespace std;

class JPrimitiveArrayClass : public JClass{
    public:
      JPrimitiveArrayClass(JClass* componentType){
          this->componentType=componentType;
          string cn=componentType->getCanonicalName();
          if (!cn.empty()){
              this->canonicalName=cn+"[]";
          }
          this->name=componentType->getSimpleName()+"[]";//not extra
          this->simpleName=componentType->getSimpleName()+"[]";
          this->bIsArray=true;
          addInterface(JSerializable::getClazz());
        }

      JClass* getSuperclass(){
          return JObject::getClazz();
      }

      JObject* newInstance(){
          return new JPrimitiveArray(componentType);
      }
};

static map<string,JPrimitiveArrayClass*>* jPrimitiveArrayClasses;

JClass* JPrimitiveArray::getClazz(JClass* componentType){//TODO use mutex
    if (jPrimitiveArrayClasses==NULL){
        jPrimitiveArrayClasses=new map<string,JPrimitiveArrayClass*>();
    }
    JPrimitiveArrayClass* jPrimitiveArrayClass=getFromMap(jPrimitiveArrayClasses,componentType->getName());
    if (jPrimitiveArrayClass==NULL){
        jPrimitiveArrayClass=new JPrimitiveArrayClass(componentType);
        jPrimitiveArrayClasses->insert(pair<string,JPrimitiveArrayClass*>(componentType->getName(),jPrimitiveArrayClass));
    }
    return jPrimitiveArrayClass;
}

JPrimitiveArray::JPrimitiveArray(JClass* arrayClass,int len):JObject(getClazz(arrayClass)){
    objects=new vector<JObject*>(len);
    this->len=len;
}

bool JPrimitiveArray::operator==(JPrimitiveArray &other){
    if (other.size()==size()){
        for (int i=0;i<other.size();i++){
            JObject* object1=other.get(i);
            JObject* object2=get(i);
            if (!(object1==object2)){
                return false;
            }
        }
        return true;
    }
    return false;
}

int JPrimitiveArray::size(){
    return len;
}

void JPrimitiveArray::setSize(int len){
    this->len=len;
}

JObject* JPrimitiveArray::get(int i){
    return objects->at(i);
}

void JPrimitiveArray::set(int i,JObject* value){
    (*objects)[i]=value;
}

JPrimitiveArray::~JPrimitiveArray(){
    deleteVectorOfPointers(objects);
}
