#include "JPrimitiveDouble.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveDoubleClass : public JClass{
          public:
            JPrimitiveDoubleClass(){
                this->canonicalName="double";
                this->name="double";
                this->simpleName="double";
                this->bIsPrimitive=true;
                addInterface(JComparable::getClazz());
                addInterface(JSerializable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveDouble(0);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveDouble::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveDoubleClass();
            }
            return clazz;
        }

        JPrimitiveDouble::JPrimitiveDouble(jdouble value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveDouble::JPrimitiveDouble():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveDouble::compareTo(JObject* o){
            JPrimitiveDouble* s=dynamic_cast<JPrimitiveDouble*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveDouble::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveDouble* s=dynamic_cast<JPrimitiveDouble*>(other);
            return value==s->value;
        }

        JPrimitiveDouble JPrimitiveDouble::operator+=(jdouble f){
            value+=f;
            return *this;
        }

        JPrimitiveDouble JPrimitiveDouble::operator-=(jdouble f){
            value-=f;
            return *this;
        }

        JPrimitiveDouble JPrimitiveDouble::operator*=(jdouble f){
            value*=f;
            return *this;
        }

        void JPrimitiveDouble::set(jdouble value){
            this->value=value;
        }

        jdouble JPrimitiveDouble::get(){
            return value;
        }

        jint JPrimitiveDouble::hashCode(){
            return (jint)value;
        }

        string JPrimitiveDouble::toString(){
            stringstream ss;
            ss<<value;
            return ss.str();
        }

        JPrimitiveDouble::~JPrimitiveDouble(){
        }
    }
}

