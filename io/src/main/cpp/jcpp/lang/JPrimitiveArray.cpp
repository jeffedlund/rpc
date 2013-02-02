#include "JPrimitiveArray.h"
#include "JClass.h"
#include "Collections.h"
#include <map>
#include <vector>
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
        }

      JClass* getSuperclass(){
          return JObject::getClazz();
      }

      JObject* newInstance(){
          return new JPrimitiveArray(componentType);
      }
};

static map<string,JPrimitiveArray*>* jPrimitiveArrays=new map<string,JPrimitiveArray*>();

static JPrimitiveArray* getJPrimitiveArray(JClass* jclass){//TODO use mutex
    JPrimitiveArray* jPrimitiveArray=jPrimitiveArrays->at(jclass->getName());
    if (jPrimitiveArray==NULL){
        jPrimitiveArray=new JPrimitiveArray(jclass);
        jPrimitiveArrays->insert(pair<string,JPrimitiveArray*>(jclass->getName(),jPrimitiveArray));
    }
    return jPrimitiveArray;
}

JPrimitiveArray::JPrimitiveArray(JClass* arrayClass):JObject(getJPrimitiveArray(arrayClass)){
    objects=new vector<JObject*>;
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
