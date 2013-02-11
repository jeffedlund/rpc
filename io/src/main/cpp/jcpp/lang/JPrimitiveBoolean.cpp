#include "JPrimitiveBoolean.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveBooleanClass : public JClass{
          public:
            JPrimitiveBooleanClass(){
                this->canonicalName="boolean";
                this->name="boolean";
                this->simpleName="boolean";
                this->bIsPrimitive=true;
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

        void JPrimitiveBoolean::set(jbool value){
            this->value=value;
        }

        jbool JPrimitiveBoolean::get(){
            return value;
        }

        string JPrimitiveBoolean::toString(){
            return (this->value?"true":"false");
        }

        JPrimitiveBoolean::~JPrimitiveBoolean(){
        }
    }
}
