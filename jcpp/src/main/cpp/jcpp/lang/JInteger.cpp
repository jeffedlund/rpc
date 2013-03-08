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

        JInteger::JInteger(jint value):JNumber(getClazz()){
            this->value=new JPrimitiveInt(value);
        }

        JInteger::JInteger():JNumber(getClazz()){
            this->value=new JPrimitiveInt(0);
        }

        bool JInteger::operator==(JObject &other){
            if (other.getClass()==getClazz()){
                JInteger* s=dynamic_cast<JInteger*>(&other);
                return (*value)==(*s->value);
            }
            return false;
        }

        void JInteger::set(jint value){
            this->value->set(value);
        }

        jint JInteger::get(){
            return value->get();
        }

        void JInteger::setPrimitiveInt(JPrimitiveInt* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveInt* JInteger::getPrimitiveInt(){
            return value;
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
