#include "JPrimitiveInt.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveIntClass : public JClass{
          public:
            JPrimitiveIntClass():JClass(){
                this->canonicalName="int";
                this->name="int";
                this->simpleName="int";
                this->bIsPrimitive=true;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveInt(0);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveInt::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveIntClass();
            }
            return clazz;
        }

        JPrimitiveInt::JPrimitiveInt(jint value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveInt::JPrimitiveInt(JPrimitiveInt* value):JObject(getClazz()){
            this->value=value->value;
        }

        JPrimitiveInt::JPrimitiveInt():JObject(getClazz()){
            this->value=0;
        }

        bool JPrimitiveInt::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveInt* s=dynamic_cast<JPrimitiveInt*>(other);
            return value==s->value;
        }

        JPrimitiveInt JPrimitiveInt::operator+=(jint f){
            value+=f;
            return *this;
        }

        JPrimitiveInt JPrimitiveInt::operator-=(jint f){
            value-=f;
            return *this;
        }

        JPrimitiveInt JPrimitiveInt::operator*=(jint f){
            value*=f;
            return *this;
        }

        void JPrimitiveInt::set(jint value){
            this->value=value;
        }

        jint JPrimitiveInt::get(){
            return value;
        }

        JPrimitiveInt* JPrimitiveInt::clone(){
            return new JPrimitiveInt(value);
        }

        jint JPrimitiveInt::hashCode(){
            return value;
        }

        string JPrimitiveInt::toString(){
            stringstream sstr;
            sstr<<value;
            return sstr.str();
        }

        JPrimitiveInt::~JPrimitiveInt(){
        }
    }
}
