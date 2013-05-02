#include "JChar.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCharClass : public JClass{
        protected:
            static JObject* staticGetValue(JObject* object){
                JChar* b=(JChar*)object;
                return b->getPrimitiveChar();
            }

            static void staticSetValue(JObject* obj,JObject* value){
                JChar* b=(JChar*)obj;
                b->setPrimitiveChar((JPrimitiveChar*)value);
            }
        public:
            JCharClass(){
                this->canonicalName="java.lang.Character";
                this->name="java.lang.Character";
                this->simpleName="Character";
                this->serialVersionUID=3786198910865385080ULL;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addField(new JField("value",JPrimitiveChar::getClazz(),this,staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JChar((jchar)0);
            }
        };

        static JClass* clazz;

        JClass* JChar::getClazz(){
            if (clazz==NULL){
                clazz=new JCharClass();
            }
            return clazz;
        }

        jint JChar::hashCode(jchar c){
            return (jint)c;
        }

        jint JChar::compare(jchar x,jchar y){
            return x-y;
        }

        jchar JChar::MIN_VALUE = (jchar)0;

        jchar JChar::MAX_VALUE = (jchar)'\uffff';

        JClass* JChar::TYPE = JPrimitiveChar::getClazz();

        JChar::JChar(char value):JObject(getClazz()){
            this->value=new JPrimitiveChar(value);
        }

        JChar::JChar(jchar value):JObject(getClazz()){
            this->value=new JPrimitiveChar(value);
        }

        JChar::JChar():JObject(getClazz()){
            this->value=new JPrimitiveChar((jchar)0);
        }

        bool JChar::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JChar* s=dynamic_cast<JChar*>(other);
                return (*value)==(*s->value);
            }
            return false;
        }

        void JChar::set(jchar value){
            this->value->set(value);
        }

        jchar JChar::get(){
            return value->get();
        }

        jchar JChar::charValue(){
            return value->get();
        }

        void JChar::setPrimitiveChar(JPrimitiveChar* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveChar* JChar::getPrimitiveChar(){
            return value;
        }

        jint JChar::compareTo(JObject *o){
            JChar* c=dynamic_cast<JChar*>(o);
            return compare(value->get(),c->value->get());
        }

        jint JChar::hashCode(){
            return hashCode(value->get());
        }

        string JChar::toString(){
            string s="";
            s.push_back(value->get());
            return s;
        }

        JChar::~JChar(){
            delete value;
        }
    }
}
