#include "JPrimitiveChar.h"
#include "JClass.h"
#include <vector>
#include <iostream>
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
                addInterface(JComparable::getClazz());
                addInterface(JSerializable::getClazz());
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

        JPrimitiveArray* JPrimitiveChar::toArray(JString str){
            JPrimitiveArray* a=new JPrimitiveArray(getClazz(),str.length());
            for (int i=0;i<str.length();i++){
                a->set(i,new JPrimitiveChar(str.charAt(i)));
            }
            return a;
        }

        JString JPrimitiveChar::fromArray(JPrimitiveArray* a){
            vector<jchar>* vec=new vector<jchar>();
            for (int i=0;i<a->size();i++){
                vec->push_back(((JPrimitiveChar*)a->get(i))->get());
            }
            JString s(vec);
            delete vec;
            return s;
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

        void JPrimitiveChar::set(jchar value){
            this->value=value;
        }

        jchar JPrimitiveChar::get(){
            return value;
        }

        jint JPrimitiveChar::compareTo(JObject* o){
            JPrimitiveChar* s=dynamic_cast<JPrimitiveChar*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveChar::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveChar* s=dynamic_cast<JPrimitiveChar*>(other);
            return value==s->value;
        }

        jint JPrimitiveChar::hashCode(){
            return (jint)value;
        }

        JString JPrimitiveChar::toString(){
            JString ss;
            ss<<value;
            return ss;
        }

        JPrimitiveChar::~JPrimitiveChar(){
        }
    }
}
