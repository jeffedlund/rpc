#include "JByte.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        static JObject* staticGetValue(JObject* object){
            JByte* b=(JByte*)object;
            return b->getPrimitiveByte();
        }

        static void staticSetValue(JObject* obj,JObject* value){
            JByte* b=(JByte*)obj;
            b->setPrimitiveByte((JPrimitiveByte*)value);
        }

        class JByteClass : public JClass{
          public:
            JByteClass():JClass(){
                this->canonicalName="java.lang.Byte";
                this->name="java.lang.Byte";
                this->simpleName="Byte";
                this->serialVersionUID=-7183698231559129828ULL;
                addInterface(JSerializable::getClazz());
                addField(new JField("value",JPrimitiveByte::getClazz(),staticGetValue,staticSetValue));
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

        jbyte JByte::MIN_VALUE=-128;

        jbyte JByte::MAX_VALUE=127;

        JByte::JByte(jbyte value):JNumber(getClazz()){
            this->value=new JPrimitiveByte(value);
        }

        JByte::JByte():JNumber(getClazz()){
            this->value=new JPrimitiveByte(0);
        }

        bool JByte::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JByte* b=dynamic_cast<JByte*>(other);
            return (*value)==(*b->value);
        }

        JByte JByte::operator+=(jbyte f){
            (*value)+=f;
            return *this;
        }

        JByte JByte::operator-=(jbyte f){
            (*value)-=f;
            return *this;
        }

        JByte JByte::operator*=(jbyte f){
            (*value)*=f;
            return *this;
        }

        void JByte::set(jbyte value){
            this->value->set(value);
        }

        jbyte JByte::get(){
            return value->get();
        }

        void JByte::setPrimitiveByte(JPrimitiveByte* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveByte* JByte::getPrimitiveByte(){
            return value;
        }

        string JByte::toString(){
            return ""+value->get();
        }

        JByte::~JByte(){
            delete value;
        }
    }
}
