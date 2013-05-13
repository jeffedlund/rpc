#include "JPrimitiveBoolean.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <JString.h>
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JPrimitiveBooleanClass : public JClass{
          public:
            JPrimitiveBooleanClass(){
                this->canonicalName="boolean";
                this->name="boolean";
                this->simpleName="boolean";
                this->bIsPrimitive=true;
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveBoolean(false);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveBoolean::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveBooleanClass();
            }
            return clazz;
        }

        JPrimitiveBoolean::JPrimitiveBoolean(jbool value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveBoolean::JPrimitiveBoolean():JObject(getClazz()){
            this->value=false;
        }

        jbool JPrimitiveBoolean::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveBoolean* s=dynamic_cast<JPrimitiveBoolean*>(other);
            return value==s->value;
        }

        void JPrimitiveBoolean::set(jbool value){
            this->value=value;
        }

        jbool JPrimitiveBoolean::get(){
            return value;
        }

        jint JPrimitiveBoolean::compareTo(JObject* o){
            JPrimitiveBoolean* b=dynamic_cast<JPrimitiveBoolean*>(o);
            return (get() == b->get()) ? 0 : (get() ? 1 : -1);
        }

        jint JPrimitiveBoolean::hashCode(){
            return (value ? 1231 : 1237);
        }

        JString JPrimitiveBoolean::toString(){
            return JString((this->value?"true":"false"));
        }

        JPrimitiveBoolean::~JPrimitiveBoolean(){
        }
    }
}
