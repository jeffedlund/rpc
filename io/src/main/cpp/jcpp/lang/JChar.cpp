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
        static JObject* staticGetValue(JObject* object){
            JChar* b=(JChar*)object;
            return b->getPrimitiveChar();
        }

        static void staticSetValue(JObject* obj,JObject* value){
            JChar* b=(JChar*)obj;
            b->setPrimitiveChar((JPrimitiveChar*)value);
        }

        class JCharClass : public JClass{
          public:
            JCharClass(){
                this->canonicalName="java.lang.Character";
                this->name="java.lang.Character";
                this->simpleName="Character";
                this->serialVersionUID=3786198910865385080ULL;
                addInterface(JSerializable::getClazz());
                addField(new JField("value",JPrimitiveChar::getClazz(),staticGetValue,staticSetValue));
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JChar(0);
            }
        };

        static JClass* clazz;

        JClass* JChar::getClazz(){
            if (clazz==NULL){
                clazz=new JCharClass();
            }
            return clazz;
        }

        JChar::JChar(char value):JObject(getClazz()){
            this->value=new JPrimitiveChar(value);
        }

        JChar::JChar():JObject(getClazz()){
            this->value=new JPrimitiveChar(0);
        }

        bool JChar::operator==(JObject &other){
            if (other.getClass()==getClazz()){
                JChar* s=dynamic_cast<JChar*>(&other);
                return (*value)==(*s->value);
            }
            return false;
        }

        void JChar::set(char value){
            this->value->set(value);
        }

        char JChar::get(){
            return value->get();
        }

        void JChar::setPrimitiveChar(JPrimitiveChar* value){
            delete this->value;
            this->value=value;
        }

        JPrimitiveChar* JChar::getPrimitiveChar(){
            return value;
        }

        string JChar::toString(){
            return ""+value->get();
        }

        JChar::~JChar(){
            delete value;
        }
    }
}
