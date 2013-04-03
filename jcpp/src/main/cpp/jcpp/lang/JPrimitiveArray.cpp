#include "JPrimitiveArray.h"
#include "JClass.h"
#include "Collections.h"
#include <map>
#include <vector>
#include "JSerializable.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveShort.h"
#include "JVoid.h"
#include <sstream>
#include "JInternalError.h"
#include <algorithm>
#include "JIllegalArgumentException.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JPrimitiveArrayClass : public JClass{
            public:
              JPrimitiveArrayClass(JClass* componentType){
                  this->componentType=componentType;
                  string cn=componentType->getCanonicalName();
                  if (!cn.empty()){
                      this->canonicalName=cn+"[]";
                  }else{
                      canonicalName="";
                  }
                  this->name="["+componentType->getSignature();
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

        static JObject* lockObject = new JObject();
        static map<string,JPrimitiveArrayClass*>* jPrimitiveArrayClasses;

        JClass* JPrimitiveArray::getClazz(JClass* componentType){
            lockObject->lock();
            if (jPrimitiveArrayClasses==NULL){
                jPrimitiveArrayClasses=new map<string,JPrimitiveArrayClass*>();
            }
            JPrimitiveArrayClass* jPrimitiveArrayClass=getFromMap(jPrimitiveArrayClasses,componentType->getName());
            if (jPrimitiveArrayClass==NULL){
                jPrimitiveArrayClass=new JPrimitiveArrayClass(componentType);
                jPrimitiveArrayClasses->insert(pair<string,JPrimitiveArrayClass*>(componentType->getName(),jPrimitiveArrayClass));
            }
            lockObject->unlock();
            return jPrimitiveArrayClass;
        }

        JPrimitiveArray::JPrimitiveArray(JClass* arrayClass,jint len):JObject(getClazz(arrayClass)){
            objects=new vector<JObject*>(len);
            this->len=len;
        }

        JPrimitiveArray::JPrimitiveArray(JClass* arrayClass,vector<JObject*>* objects):JObject(getClazz(arrayClass)){
            if (objects!=NULL){
                this->len=objects->size();
                this->objects=objects;
            }else{
                this->len=0;
                this->objects=NULL;
            }
        }

        bool JPrimitiveArray::equals(JObject* other){
            if (!other->getClass()->isArray()){
                return false;
            }
            JPrimitiveArray* s=dynamic_cast<JPrimitiveArray*>(other);
            if (s->size()==size()){
                for (int i=0;i<s->size();i++){
                    JObject* object1=s->get(i);
                    JObject* object2=get(i);
                    if (!((*object1)==(*object2))){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        jint JPrimitiveArray::size(){
            return len;
        }

        void JPrimitiveArray::setSize(jint len){
            this->len=len;
        }

        JObject* JPrimitiveArray::get(jint i){
            return objects->at(i);
        }

        void JPrimitiveArray::checkType(JObject* o){
            if (o!=NULL && !(o->isInstanceOf(getClass()->getComponentType()))){
                throw new JIllegalArgumentException("attempt to insert object of type "+o->getClass()->toString()+" in array of component type "+getClass()->getComponentType()->toString());
            }
        }

        void JPrimitiveArray::set(jint i,JObject* value){//TODO throw exception if greater than size
            checkType(value);
            (*objects)[i]=value;
        }

        vector<JObject*>* JPrimitiveArray::getObjects(){
            return objects;
        }

        JPrimitiveArray::~JPrimitiveArray(){
            len=0;
            if (objects!=NULL){
                deleteVectorOfPointers(objects);
            }
        }
    }
}
