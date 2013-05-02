#include "JLong.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "JSerializable.h"
#include "JByte.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JLongClass : public JClass{
        protected:
            static JObject* staticGetValue(JObject* object){
                JLong* b=(JLong*)object;
                return b->getPrimitiveLong();
            }

            static void staticSetValue(JObject* obj,JObject* value){
                JLong* b=(JLong*)obj;
                b->setPrimitiveLong((JPrimitiveLong*)value);
            }
        public:
            JLongClass(){
                this->canonicalName="java.lang.Long";
                this->name="java.lang.Long";
                this->simpleName="Long";
                this->serialVersionUID=4290774380558885855ULL;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addField(new JField("value",JPrimitiveLong::getClazz(),this,staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JNumber::getClazz();
            }

            JObject* newInstance(){
                return new JLong(0);
            }
        };

        static JClass* clazz;

        JClass* JLong::getClazz(){
            if (clazz==NULL){
                clazz=new JLongClass();
            }
            return clazz;
        }

        jint JLong::hashCode(jlong l){
            return (jint)l;
        }

        jint JLong::compare(jlong x,jlong y){
            return x-y;
        }

        jlong JLong::MIN_VALUE = 0x8000000000000000L;

        jlong JLong::MAX_VALUE = 0x7fffffffffffffffL;

        JClass* JLong::TYPE = JPrimitiveLong::getClazz();

        jint JLong::SIZE = 64;

        jint JLong::BYTES = SIZE / JByte::SIZE;

        JLong::JLong(jlong value):JNumber(getClazz()){
            this->value=new JPrimitiveLong(value);
        }

        JLong::JLong():JNumber(getClazz()){
            this->value=new JPrimitiveLong(0);
        }

        bool JLong::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JLong* s=dynamic_cast<JLong*>(other);
                return (*value)==(*s->value);
            }
            return false;
        }

        JLong JLong::operator+=(jlong f){
            (*value)+=f;
            return *this;
        }

        JLong JLong::operator-=(jlong f){
            (*value)-=f;
            return *this;
        }

        JLong JLong::operator*=(jlong f){
            (*value)*=f;
            return *this;
        }

        void JLong::set(jlong value){
            this->value->set(value);
        }

        jlong JLong::get(){
            return value->get();
        }

        jbyte JLong::byteValue(){
            return (jbyte)value->get();
        }

        jshort JLong::shortValue(){
            return (jshort)value->get();
        }

        jint JLong::intValue(){
            return (jint)value->get();
        }

        jlong JLong::longValue(){
            return value->get();
        }

        jfloat JLong::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JLong::doubleValue(){
            return (jdouble)value->get();
        }

        void JLong::setPrimitiveLong(JPrimitiveLong* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveLong* JLong::getPrimitiveLong(){
            return value;
        }

        jint JLong::compareTo(JObject *o){
            JLong* l=dynamic_cast<JLong*>(o);
            return compare(get(),l->get());
        }

        jint JLong::hashCode(){
            return hashCode(value->get());
        }

        string JLong::toString(){
            stringstream ss;
            ss<<value->get();
            return ss.str();
        }

        JLong::~JLong(){
            delete value;
        }
    }
}
