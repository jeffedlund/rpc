#include "JPrimitiveFloat.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveFloatClass : public JClass{
          public:
            JPrimitiveFloatClass(){
                this->canonicalName="float";
                this->name="float";
                this->simpleName="float";
                this->bIsPrimitive=true;
                addInterface(JComparable::getClazz());
                addInterface(JSerializable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveFloat(0);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveFloat::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveFloatClass();
            }
            return clazz;
        }

        JPrimitiveFloat::JPrimitiveFloat(jfloat value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveFloat::JPrimitiveFloat():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveFloat::compareTo(JObject* o){
            JPrimitiveFloat* s=dynamic_cast<JPrimitiveFloat*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveFloat::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveFloat* s=dynamic_cast<JPrimitiveFloat*>(other);
            return value==s->value;
        }

        JPrimitiveFloat JPrimitiveFloat::operator+=(jfloat f){
            value+=f;
            return *this;
        }

        JPrimitiveFloat JPrimitiveFloat::operator-=(jfloat f){
            value-=f;
            return *this;
        }

        JPrimitiveFloat JPrimitiveFloat::operator*=(jfloat f){
            value*=f;
            return *this;
        }

        void JPrimitiveFloat::set(jfloat value){
            this->value=value;
        }

        jfloat JPrimitiveFloat::get(){
            return value;
        }

        jint JPrimitiveFloat::hashCode(){
            return (jint)value;
        }

        string JPrimitiveFloat::toString(){
            stringstream ss;
            ss<<value;
            return ss.str();
        }

        JPrimitiveFloat::~JPrimitiveFloat(){
        }
    }
}
