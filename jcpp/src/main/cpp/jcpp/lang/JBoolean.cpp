#include "JBoolean.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        static JObject* getValue(JObject* object){
            JBoolean* b=(JBoolean*)object;
            return b->getPrimitiveBoolean();
        }

        static void setValue(JObject* obj,JObject* value){
            JBoolean* b=(JBoolean*)obj;
            b->setPrimitiveBoolean((JPrimitiveBoolean*)value);
        }

        class JBooleanClass : public JClass{
          public:
            JBooleanClass(){
                this->canonicalName="java.lang.Boolean";
                this->name="java.lang.Boolean";
                this->simpleName="Boolean";
                this->serialVersionUID=-3665804199014368530ULL;
                addInterface(JSerializable::getClazz());
                addField(new JField("value",JPrimitiveBoolean::getClazz(),getValue,setValue));
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JBoolean(false);
            }
        };

        static JClass* clazz;

        JClass* JBoolean::getClazz(){
            if (clazz==NULL){
                clazz=new JBooleanClass();
            }
            return clazz;
        }

        jint JBoolean::hashCode(bool value){
            return (value ? 1231 : 1237);
        }

        JBoolean::JBoolean(bool value):JObject(getClazz()){
            this->value=new JPrimitiveBoolean(value);
        }

        JBoolean::JBoolean():JObject(getClazz()){
            this->value=new JPrimitiveBoolean(false);
        }

        bool JBoolean::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JBoolean* b=dynamic_cast<JBoolean*>(other);
            return (*value)==(*b->value);
        }

        void JBoolean::set(bool value){
            this->value->set(value);
        }

        bool JBoolean::get(){
            return value->get();
        }

        JPrimitiveBoolean* JBoolean::getPrimitiveBoolean(){
            return value;
        }

        void JBoolean::setPrimitiveBoolean(JPrimitiveBoolean* value){
            delete this->value;
            this->value=value;
        }

        jint JBoolean::hashCode(){
            return hashCode(value->get());
        }

        string JBoolean::toString(){
            return (value!=NULL && value->get()?"true":"false");
        }

        JBoolean::~JBoolean(){
            delete value;
        }
    }
}
