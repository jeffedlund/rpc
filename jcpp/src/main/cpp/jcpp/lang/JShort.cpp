#include "JShort.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "JSerializable.h"
#include "JPrimitiveShort.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        static JObject* staticGetValue(JObject* object){
            JShort* s=(JShort*)object;
            return s->getPrimitiveShort();
        }

        static void staticSetValue(JObject* object,JObject* value){
            JShort* s=(JShort*)object;
            s->setPrimitiveShort((JPrimitiveShort*)value);
        }

        class JShortClass : public JClass{
          public:
            JShortClass(){
                this->canonicalName="java.lang.Short";
                this->name="java.lang.Short";
                this->simpleName="Short";
                this->serialVersionUID=7515723908773894738ULL;
                addInterface(JSerializable::getClazz());
                addField(new JField("value",JPrimitiveShort::getClazz(),staticGetValue,staticSetValue));
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

        jshort JShort::MIN_VALUE = -32768;

        jshort JShort::MAX_VALUE = 32767;

        JShort::JShort(jshort value):JNumber(getClazz()){
            this->value=new JPrimitiveShort(value);
        }

        JShort::JShort():JNumber(getClazz()){
            this->value=new JPrimitiveShort(0);
        }

        bool JShort::operator==(JObject &other){
            if (other.getClass()==getClazz()){
                JShort* s=dynamic_cast<JShort*>(&other);
                return (*value)==(*s->value);
            }
            return false;
        }

        JShort JShort::operator+=(jshort f){
            (*value)+=f;
            return *this;
        }

        JShort JShort::operator-=(jshort f){
            (*value)-=f;
            return *this;
        }

        JShort JShort::operator*=(jshort f){
            (*value)*=f;
            return *this;
        }

        void JShort::set(jshort value){
            this->value->set(value);
        }

        jshort JShort::get(){
            return value->get();
        }

        void JShort::setPrimitiveShort(JPrimitiveShort* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveShort* JShort::getPrimitiveShort(){
            return value;
        }

        string JShort::toString(){
            stringstream ss;
            ss<<value->get();
            return ss.str();
        }

        JShort::~JShort(){
            delete value;
        }
    }
}
