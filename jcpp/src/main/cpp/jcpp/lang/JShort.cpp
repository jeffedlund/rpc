#include "JShort.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "JSerializable.h"
#include "JPrimitiveShort.h"
#include "JByte.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JShortClass : public JClass{
        protected:
            static JObject* staticGetValue(JObject* object){
                JShort* s=(JShort*)object;
                return s->getPrimitiveShort();
            }

            static void staticSetValue(JObject* object,JObject* value){
                JShort* s=(JShort*)object;
                s->setPrimitiveShort((JPrimitiveShort*)value);
            }
        public:
            JShortClass(){
                this->canonicalName="java.lang.Short";
                this->name="java.lang.Short";
                this->simpleName="Short";
                this->serialVersionUID=7515723908773894738ULL;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addField(new JField("value",JPrimitiveShort::getClazz(),this,staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JNumber::getClazz();
            }

            JObject* newInstance(){
                return new JShort(0);
            }
        };

        static JClass* clazz;

        JClass* JShort::getClazz(){
            if (clazz==NULL){
                clazz=new JShortClass();
            }
            return clazz;
        }

        jint JShort::hashCode(jshort s){
            return (jint)s;
        }

        jint JShort::compare(jshort x, jshort y){
            return x-y;
        }

        jshort JShort::MIN_VALUE = -32768;

        jshort JShort::MAX_VALUE = 32767;

        jint JShort::SIZE = 16;

        jint JShort::BYTES = SIZE / JByte::SIZE;

        JClass* JShort::TYPE = JPrimitiveShort::getClazz();

        JShort::JShort(jshort value):JNumber(getClazz()){
            this->value=new JPrimitiveShort(value);
        }

        JShort::JShort():JNumber(getClazz()){
            this->value=new JPrimitiveShort(0);
        }

        jint JShort::compareTo(JObject* o){
            JShort* s=dynamic_cast<JShort*>(o);
            return compare(get(),s->get());
        }

        jbool JShort::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JShort* s=dynamic_cast<JShort*>(other);
                return (*value)==(*s->value);
            }
            return false;
        }

        JShort& JShort::operator+=(jshort f){
            (*value)+=f;
            return *this;
        }

        JShort& JShort::operator-=(jshort f){
            (*value)-=f;
            return *this;
        }

        JShort& JShort::operator*=(jshort f){
            (*value)*=f;
            return *this;
        }

        void JShort::set(jshort value){
            this->value->set(value);
        }

        jshort JShort::get(){
            return value->get();
        }

        jbyte JShort::byteValue(){
            return (jbyte)value->get();
        }

        jshort JShort::shortValue(){
            return value->get();
        }

        jint JShort::intValue(){
            return (jint)value->get();
        }

        jlong JShort::longValue(){
            return (jlong)value->get();
        }

        jfloat JShort::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JShort::doubleValue(){
            return (jdouble)value->get();
        }

        void JShort::setPrimitiveShort(JPrimitiveShort* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveShort* JShort::getPrimitiveShort(){
            return value;
        }

        jint JShort::hashCode(){
            return hashCode(value->get());
        }

        JString JShort::toString(){
            JString ss;
            ss<<value->get();
            return ss;
        }

        JShort::~JShort(){
            delete value;
        }
    }
}
