#include "JByte.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JSerializable.h"
#include "JString.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JByteClass : public JClass{
        protected:
            static JObject* staticGetValue(JObject* object){
                JByte* b=(JByte*)object;
                return b->getPrimitiveByte();
            }

            static void staticSetValue(JObject* obj,JObject* value){
                JByte* b=(JByte*)obj;
                b->setPrimitiveByte((JPrimitiveByte*)value);
            }
        public:
            JByteClass():JClass(){
                this->canonicalName="java.lang.Byte";
                this->name="java.lang.Byte";
                this->simpleName="Byte";
                this->serialVersionUID=-7183698231559129828ULL;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addField(new JField("value",JPrimitiveByte::getClazz(),this,staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JNumber::getClazz();
            }

            JObject* newInstance(){
                return new JByte(0);
            }
        };

        static JClass* clazz;

        JClass* JByte::getClazz(){
            if (clazz==NULL){
                clazz=new JByteClass();
            }
            return clazz;
        }

        jint JByte::hashCode(jbyte b){
            return (jint)b;
        }

        jint JByte::compare(jbyte x,jbyte y){
            return x-y;
        }

        jbyte JByte::MIN_VALUE=-128;

        jbyte JByte::MAX_VALUE=127;

        JClass* JByte::TYPE = JPrimitiveByte::getClazz();

        jint JByte::toUnsignedInt(jbyte x){
            return ((jint) x) & 0xff;
        }

        jlong JByte::toUnsignedLong(jbyte x){
            return ((jlong) x) & 0xffL;
        }

        jint JByte::SIZE = 8;

        jint JByte::BYTES = SIZE / JByte::SIZE;

        JByte::JByte(jbyte value):JNumber(getClazz()){
            this->value=new JPrimitiveByte(value);
        }

        JByte::JByte():JNumber(getClazz()){
            this->value=new JPrimitiveByte(0);
        }

        jbool JByte::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JByte* b=dynamic_cast<JByte*>(other);
            return (*value)==(*b->value);
        }

        JByte& JByte::operator+=(jbyte f){
            (*value)+=f;
            return *this;
        }

        JByte& JByte::operator-=(jbyte f){
            (*value)-=f;
            return *this;
        }

        JByte& JByte::operator*=(jbyte f){
            (*value)*=f;
            return *this;
        }

        void JByte::set(jbyte value){
            this->value->set(value);
        }

        jbyte JByte::get(){
            return value->get();
        }

        jbyte JByte::byteValue(){
            return value->get();
        }

        jshort JByte::shortValue() {
            return (jshort)value->get();
        }

        jint JByte::intValue(){
            return (jint)value->get();
        }

        jlong JByte::longValue(){
            return (jlong)value->get();
        }

        jfloat JByte::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JByte::doubleValue(){
            return (jdouble)value->get();
        }

        void JByte::setPrimitiveByte(JPrimitiveByte* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveByte* JByte::getPrimitiveByte(){
            return value;
        }

        jint JByte::compareTo(JObject *o){
            JByte* b=dynamic_cast<JByte*>(o);
            return compare(value->get(),b->get());
        }

        jint JByte::hashCode(){
            return hashCode(value->get());
        }

        JString JByte::toString(){
            JString s("");
            s<<value->get();
            return s;
        }

        JByte::~JByte(){
            delete value;
        }
    }
}
