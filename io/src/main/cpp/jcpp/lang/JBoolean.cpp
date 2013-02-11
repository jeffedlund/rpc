#include "JBoolean.h"
#include "JClass.h"
#include <QtGlobal>
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

        JBoolean::JBoolean(bool value):JObject(getClazz()){
            this->value=new JPrimitiveBoolean(value);
        }

        JBoolean::JBoolean():JObject(getClazz()){
            this->value=false;
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
            this->value=value;
        }

        string JBoolean::toString(){
            return (value!=NULL && value->get()?"true":"false");
        }

        JBoolean::~JBoolean(){
            delete value;
        }
    }
}
