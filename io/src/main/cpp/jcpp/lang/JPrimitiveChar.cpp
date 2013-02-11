#include "JPrimitiveChar.h"
#include "JClass.h"
#include <QtGlobal>
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
                return new JPrimitiveChar(0);
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

        JPrimitiveChar::JPrimitiveChar():JObject(getClazz()){
            this->value=0;
        }

        void JPrimitiveChar::set(char value){
            this->value=value;
        }

        char JPrimitiveChar::get(){
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
