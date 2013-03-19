#include "JFloat.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        static JObject* staticGetValue(JObject* object){
            JFloat* b=(JFloat*)object;
            return b->getPrimitiveFloat();
        }

        static void staticSetValue(JObject* obj,JObject* value){
            JFloat* b=(JFloat*)obj;
            b->setPrimitiveFloat((JPrimitiveFloat*)value);
        }

        class JFloatClass : public JClass{
          public:
            JFloatClass(){
                this->canonicalName="java.lang.Float";
                this->name="java.lang.Float";
                this->simpleName="Float";
                this->serialVersionUID=-2671257302660747028ULL;
                addInterface(JSerializable::getClazz());
                addField(new JField("value",JPrimitiveFloat::getClazz(),staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JNumber::getClazz();
            }

            JObject* newInstance(){
                return new JFloat(0);
            }
        };

        static JClass* clazz;

        JClass* JFloat::getClazz(){
            if (clazz==NULL){
                clazz=new JFloatClass();
            }
            return clazz;
        }

        jfloat JFloat::MIN_VALUE = 0x0.000002P-126f;

        jfloat JFloat::MAX_VALUE = 0x1.fffffeP+127f;

        JFloat::JFloat(float value):JNumber(getClazz()){
            this->value=new JPrimitiveFloat(value);
        }

        JFloat::JFloat():JNumber(getClazz()){
            this->value=new JPrimitiveFloat(0);
        }

        bool JFloat::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JFloat* s=dynamic_cast<JFloat*>(other);
                return (*value)==(*s->value);
            }
            return false;
        }

        JFloat JFloat::operator+=(jfloat f){
            (*value)+=f;
            return *this;
        }

        JFloat JFloat::operator-=(jfloat f){
            (*value)-=f;
            return *this;
        }

        JFloat JFloat::operator*=(jfloat f){
            (*value)*=f;
            return *this;
        }

        void JFloat::set(float value){
            this->value->set(value);
        }

        float JFloat::get(){
            return value->get();
        }

        void JFloat::setPrimitiveFloat(JPrimitiveFloat* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveFloat* JFloat::getPrimitiveFloat(){
            return value;
        }

        string JFloat::toString(){
            stringstream ss;
            ss<<value->get();
            return ss.str();
        }

        JFloat::~JFloat(){
            delete value;
        }
    }
}
