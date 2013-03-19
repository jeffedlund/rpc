#include "JPrimitiveChar.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveCharClass : public JClass{
          public:
            JPrimitiveCharClass(){
                this->canonicalName="char";
                this->name="char";
                this->simpleName="char";
                this->bIsPrimitive=true;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveChar((jchar)0);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveChar::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveCharClass();
            }
            return clazz;
        }

        JPrimitiveChar::JPrimitiveChar(char value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveChar::JPrimitiveChar(jchar value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveChar::JPrimitiveChar():JObject(getClazz()){
            this->value=0;
        }

        bool JPrimitiveChar::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveChar* s=dynamic_cast<JPrimitiveChar*>(other);
            return value==s->value;
        }

        void JPrimitiveChar::set(jchar value){
            this->value=value;
        }

        jchar JPrimitiveChar::get(){
            return value;
        }

        string JPrimitiveChar::toString(){
            stringstream ss;
            ss<<value;
            return ss.str();
        }

        JPrimitiveChar::~JPrimitiveChar(){
        }
    }
}
