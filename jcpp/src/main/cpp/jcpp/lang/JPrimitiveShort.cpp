#include "JPrimitiveShort.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveShortClass : public JClass{
          public:
            JPrimitiveShortClass(){
                this->canonicalName="short";
                this->name="short";
                this->simpleName="short";
                this->bIsPrimitive=true;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveShort(0);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveShort::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveShortClass();
            }
            return clazz;
        }

        JPrimitiveShort::JPrimitiveShort(jshort value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveShort::JPrimitiveShort():JObject(getClazz()){
            this->value=0;
        }

        bool JPrimitiveShort::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveShort* s=dynamic_cast<JPrimitiveShort*>(other);
            return value==s->value;
        }

        JPrimitiveShort JPrimitiveShort::operator+=(jshort f){
            value+=f;
            return *this;
        }

        JPrimitiveShort JPrimitiveShort::operator-=(jshort f){
            value-=f;
            return *this;
        }

        JPrimitiveShort JPrimitiveShort::operator*=(jshort f){
            value*=f;
            return *this;
        }

        void JPrimitiveShort::set(jshort value){
            this->value=value;
        }

        jshort JPrimitiveShort::get(){
            return value;
        }

        string JPrimitiveShort::toString(){
            stringstream ss;
            ss<<value;
            return ss.str();
        }

        JPrimitiveShort::~JPrimitiveShort(){
        }
    }
}
