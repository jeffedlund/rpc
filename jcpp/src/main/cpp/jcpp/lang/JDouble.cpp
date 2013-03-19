#include "JDouble.h"
#include "JNumber.h"
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
            JDouble* b=(JDouble*)object;
            return b->getPrimitiveDouble();
        }

        static void staticSetValue(JObject* obj,JObject* value){
            JDouble* b=(JDouble*)obj;
            b->setPrimitiveDouble((JPrimitiveDouble*)value);
        }

        class JDoubleClass : public JClass{
          public:
            JDoubleClass(){
                this->canonicalName="java.lang.Double";
                this->name="java.lang.Double";
                this->simpleName="Double";
                this->serialVersionUID=-9172774392245257468ULL;
                addInterface(JSerializable::getClazz());
                addField(new JField("value",JPrimitiveDouble::getClazz(),staticGetValue,staticSetValue));
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

        jdouble JDouble::MIN_VALUE = 0x0.0000000000001P-1022;

        jdouble JDouble::MAX_VALUE = 0x1.fffffffffffffP+1023;

        JDouble::JDouble(double value):JNumber(JDouble::getClazz()){
            this->value=new JPrimitiveDouble(value);
        }

        JDouble::JDouble():JNumber(JDouble::getClazz()){
            this->value=new JPrimitiveDouble(0);
        }

        bool JDouble::operator==(JObject &other){
            if (other.getClass()==getClazz()){
                JDouble* s=dynamic_cast<JDouble*>(&other);
                return (*value)==(*s->value);
            }
            return false;
        }

        JDouble JDouble::operator+=(jdouble f){
            (*value)+=f;
            return *this;
        }

        JDouble JDouble::operator-=(jdouble f){
            (*value)-=f;
            return *this;
        }

        JDouble JDouble::operator*=(jdouble f){
            (*value)*=f;
            return *this;
        }

        void JDouble::set(double value){
            this->value->set(value);
        }

        double JDouble::get(){
            return value->get();
        }

        void JDouble::setPrimitiveDouble(JPrimitiveDouble* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveDouble* JDouble::getPrimitiveDouble(){
            return value;
        }

        string JDouble::toString(){
            stringstream ss;
            ss<<value->get();
            return ss.str();
        }

        JDouble::~JDouble(){
            delete value;
        }
    }
}
