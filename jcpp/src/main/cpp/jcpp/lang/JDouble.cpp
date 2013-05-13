#include "JDouble.h"
#include "JNumber.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "JSerializable.h"
#include "JByte.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JDoubleClass : public JClass{
        protected:
            static JObject* staticGetValue(JObject* object){
                JDouble* b=(JDouble*)object;
                return b->getPrimitiveDouble();
            }

            static void staticSetValue(JObject* obj,JObject* value){
                JDouble* b=(JDouble*)obj;
                b->setPrimitiveDouble((JPrimitiveDouble*)value);
            }
        public:
            JDoubleClass(){
                this->canonicalName="java.lang.Double";
                this->name="java.lang.Double";
                this->simpleName="Double";
                this->serialVersionUID=-9172774392245257468ULL;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addField(new JField("value",JPrimitiveDouble::getClazz(),this,staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JNumber::getClazz();
            }

            JObject* newInstance(){
                return new JDouble(0);
            }
        };

        static JClass* clazz;

        JClass* JDouble::getClazz(){
            if (clazz==NULL){
                clazz=new JDoubleClass();
            }
            return clazz;
        }

        jint JDouble::hashCode(jdouble d){
            return (jint)d;
        }

        jint JDouble::compare(jdouble d1,jdouble d2){
            return d1-d2;
        }

        jdouble JDouble::MIN_VALUE = 0x0.0000000000001P-1022;

        jdouble JDouble::MAX_VALUE = 0x1.fffffffffffffP+1023;

        jint JDouble::SIZE = 64;

        jint JDouble::BYTES = SIZE / JByte::SIZE;

        JClass* JDouble::TYPE = JPrimitiveDouble::getClazz();

        JDouble::JDouble(double value):JNumber(JDouble::getClazz()){
            this->value=new JPrimitiveDouble(value);
        }

        JDouble::JDouble():JNumber(JDouble::getClazz()){
            this->value=new JPrimitiveDouble(0);
        }

        bool JDouble::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JDouble* s=dynamic_cast<JDouble*>(other);
                return (*value)==(*s->value);
            }
            return false;
        }

        JDouble& JDouble::operator+=(jdouble f){
            (*value)+=f;
            return *this;
        }

        JDouble& JDouble::operator-=(jdouble f){
            (*value)-=f;
            return *this;
        }

        JDouble& JDouble::operator*=(jdouble f){
            (*value)*=f;
            return *this;
        }

        void JDouble::set(jdouble value){
            this->value->set(value);
        }

        jdouble JDouble::get(){
            return value->get();
        }

        jbyte JDouble::byteValue(){
            return (jbyte)value->get();
        }

        jshort JDouble::shortValue(){
            return (jshort)value->get();
        }

        jint JDouble::intValue(){
            return (jint)value->get();
        }

        jlong JDouble::longValue(){
            return (jlong)value->get();
        }

        jfloat JDouble::floatValue(){
            return (jfloat)value->get();
        }

        jdouble JDouble::doubleValue(){
            return value->get();
        }

        void JDouble::setPrimitiveDouble(JPrimitiveDouble* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveDouble* JDouble::getPrimitiveDouble(){
            return value;
        }

        jint JDouble::compareTo(JObject *o){
            JDouble* d=dynamic_cast<JDouble*>(o);
            return compare(value->get(),d->get());
        }

        jint JDouble::hashCode(){
            return hashCode(value->get());
        }

        JString JDouble::toString(){
            JString ss;
            ss<<value->get();
            return ss;
        }

        JDouble::~JDouble(){
            delete value;
        }
    }
}
