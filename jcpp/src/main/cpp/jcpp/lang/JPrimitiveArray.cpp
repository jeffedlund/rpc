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

        JClass* JPrimitiveArray::loadClassBySignature(JClassLoader* classLoader,string name){
            if (name.at(0)=='['){
                int nbArray=0;
                string classname;
                for (unsigned int i=0;i<name.size();i++){
                    if (name.at(i)=='['){
                        nbArray++;
                    }else{
                        classname=name.substr(i,name.size());
                        break;
                    }
                }
                JClass* componentClass;
                if (classname=="I"){
                    componentClass= JPrimitiveInt::getClazz();
                }else if (classname=="B"){
                    componentClass= JPrimitiveByte::getClazz();
                }else if (classname=="J"){
                    componentClass= JPrimitiveLong::getClazz();
                }else if (classname=="F"){
                    componentClass= JPrimitiveFloat::getClazz();
                }else if (classname=="D"){
                    componentClass= JPrimitiveDouble::getClazz();
                }else if (classname=="S"){
                    componentClass= JPrimitiveShort::getClazz();
                }else if (classname=="C"){
                    componentClass= JPrimitiveChar::getClazz();
                }else if (classname=="Z"){
                    componentClass= JPrimitiveBoolean::getClazz();
                }else if (classname=="V"){
                    componentClass= JVoid::getClazz();
                }else if (classname.at(0)=='L'){
                    classname=classname.substr(1,classname.size()-2);//remove ;
                    replace(classname.begin(),classname.end(),'/','.');
                    componentClass=classLoader->loadClass(classname);
                }else{
                    throw new JInternalError();
                }
                JClass* current=componentClass;
                for (int i=0;i<nbArray;i++){
                    current=getClazz(current);
                }
                return current;
            }
            throw new JInternalError();
        }

        JPrimitiveArray::JPrimitiveArray(JClass* arrayClass,int len):JObject(getClazz(arrayClass)){
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

        int JPrimitiveArray::size(){
            return len;
        }

        void JPrimitiveArray::setSize(int len){
            this->len=len;
        }

        JObject* JPrimitiveArray::get(int i){
            return objects->at(i);
        }

        void JPrimitiveArray::set(int i,JObject* value){//TODO throw exception if greater than size
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
