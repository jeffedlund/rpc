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

        JPrimitiveDouble::JPrimitiveDouble(double value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveDouble::JPrimitiveDouble():JObject(getClazz()){
            this->value=0;
        }

        bool JPrimitiveDouble::operator==(JObject &other){
            if (other.getClass()!=getClazz()){
                return false;
            }
            JPrimitiveDouble* s=dynamic_cast<JPrimitiveDouble*>(&other);
            return value==s->value;
        }

        void JPrimitiveDouble::set(double value){
            this->value=value;
        }

        double JPrimitiveDouble::get(){
            return value;
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

