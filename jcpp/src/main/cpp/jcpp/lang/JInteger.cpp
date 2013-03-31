#include "JInteger.h"
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
            JInteger* b=(JInteger*)object;
            return b->getPrimitiveInt();
        }

        static void staticSetValue(JObject* obj,JObject* value){
            JInteger* b=(JInteger*)obj;
            b->setPrimitiveInt((JPrimitiveInt*)value);
        }

        class JIntegerClass : public JClass{
          public:
            JIntegerClass(){
                this->canonicalName="java.lang.Integer";
                this->name="java.lang.Integer";
                this->simpleName="Integer";
                this->serialVersionUID=1360826667806852920ULL;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addField(new JField("value",JPrimitiveInt::getClazz(),staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JNumber::getClazz();
            }

            JObject* newInstance(){
                return new JInteger(0);
            }
        };

        static JClass* clazz;

        JClass* JInteger::getClazz(){
            if (clazz==NULL){
                clazz=new JIntegerClass();
            }
            return clazz;
        }

        jint JInteger::hashCode(jint i){
            return i;
        }

        jint JInteger::compare(jint x,jint y){
            return x-y;
        }

        jint JInteger::MIN_VALUE = 0x80000000;

        jint JInteger::MAX_VALUE = 0x7fffffff;

        JInteger::JInteger(jint value):JNumber(getClazz()){
            this->value=new JPrimitiveInt(value);
        }

        JInteger::JInteger():JNumber(getClazz()){
            this->value=new JPrimitiveInt(0);
        }

        bool JInteger::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JInteger* s=dynamic_cast<JInteger*>(other);
                return (*value)==(*s->value);
            }
            return false;
        }

        JInteger JInteger::operator+=(jint f){
            (*value)+=f;
            return *this;
        }

        JInteger JInteger::operator-=(jint f){
            (*value)-=f;
            return *this;
        }

        JInteger JInteger::operator*=(jint f){
            (*value)*=f;
            return *this;
        }

        void JInteger::set(jint value){
            this->value->set(value);
        }

        jint JInteger::get(){
            return value->get();
        }

        jbyte JInteger::byteValue(){
            return (jbyte)value->get();
        }

        jshort JInteger::shortValue(){
            return (jshort)value->get();
        }

        jint JInteger::intValue(){
            return value->get();
        }

        jlong JInteger::longValue(){
            return (jlong)value->get();
        }

        jfloat JInteger::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JInteger::doubleValue(){
            return (jdouble)value->get();
        }

        void JInteger::setPrimitiveInt(JPrimitiveInt* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveInt* JInteger::getPrimitiveInt(){
            return value;
        }

        jint JInteger::compareTo(JObject *o){
            JInteger* i=dynamic_cast<JInteger*>(o);
            return compare(get(),i->get());
        }

        jint JInteger::hashCode(){
            return hashCode(value->get());
        }

        string JInteger::toString(){
            stringstream ss;
            ss<<value->get();
            return ss.str();
        }

        JInteger::~JInteger(){
            delete value;
        }
    }
}
