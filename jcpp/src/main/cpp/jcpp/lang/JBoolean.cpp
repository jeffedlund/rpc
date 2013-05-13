#include "JBoolean.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JBooleanClass : public JClass{
        protected:
            static JObject* getValue(JObject* object){
                JBoolean* b=(JBoolean*)object;
                return b->getPrimitiveBoolean();
            }

            static void setValue(JObject* obj,JObject* value){
                JBoolean* b=(JBoolean*)obj;
                b->setPrimitiveBoolean((JPrimitiveBoolean*)value);
            }

          public:
            JBooleanClass(){
                this->canonicalName="java.lang.Boolean";
                this->name="java.lang.Boolean";
                this->simpleName="Boolean";
                this->serialVersionUID=-3665804199014368530ULL;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addField(new JField("value",JPrimitiveBoolean::getClazz(),this,getValue,setValue));
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

        JBoolean* JBoolean::TRUE = new JBoolean(true);

        JBoolean* JBoolean::FALSE = new JBoolean(false);

        JClass* JBoolean::TYPE = JPrimitiveBoolean::getClazz();

        jbool JBoolean::parseBoolean(JString s){
            return s=="true";
        }

        JBoolean* JBoolean::valueOf(jbool b){
            return (b ? TRUE : FALSE);
        }

        JBoolean* JBoolean::valueOf(JString s){
            return (parseBoolean(s) ? TRUE : FALSE );
        }

        JString JBoolean::toString(jbool b){
            return (b ? "true" : "false");
        }

        jint JBoolean::hashCode(bool value){
            return (value ? 1231 : 1237);
        }

        jint JBoolean::compare(jbool v1,jbool v2){
            return (v1 == v2) ? 0 : (v1 ? 1 : -1);
        }

        jbool JBoolean::getBoolean(JString){
            jbool result = false;//TODO  parseBoolean(System.getProperty(name));
            return result;
        }

        JBoolean::JBoolean(jbool value):JObject(getClazz()){
            this->value=new JPrimitiveBoolean(value);
        }

        JBoolean::JBoolean():JObject(getClazz()){
            this->value=new JPrimitiveBoolean(false);
        }

        jbool JBoolean::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JBoolean* b=dynamic_cast<JBoolean*>(other);
            return (*value)==(*b->value);
        }

        void JBoolean::set(jbool value){
            this->value->set(value);
        }

        jbool JBoolean::get(){
            return value->get();
        }

        jbool JBoolean::booleanValue(){
            return value->get();
        }

        JPrimitiveBoolean* JBoolean::getPrimitiveBoolean(){
            return value;
        }

        void JBoolean::setPrimitiveBoolean(JPrimitiveBoolean* value){
            delete this->value;
            this->value=value;
        }

        jint JBoolean::compareTo(JObject *o){
            JBoolean* b=dynamic_cast<JBoolean*>(o);
            return compare(value->get(),b->value->get());
        }

        jint JBoolean::hashCode(){
            return hashCode(value->get());
        }

        JString JBoolean::toString(){
            return JString((value!=NULL && value->get()?"true":"false"));
        }

        JBoolean::~JBoolean(){
            delete value;
        }
    }
}
