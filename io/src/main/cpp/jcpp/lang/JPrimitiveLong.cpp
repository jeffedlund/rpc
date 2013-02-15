#include "JPrimitiveLong.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveLongClass : public JClass{
          public:
            JPrimitiveLongClass(){
                this->canonicalName="long";
                this->name="long";
                this->simpleName="long";
                this->bIsPrimitive=true;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveLong(0);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveLong::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveLongClass();
            }
            return clazz;
        }

        JPrimitiveLong::JPrimitiveLong(jlong value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveLong::JPrimitiveLong():JObject(getClazz()){
            this->value=0;
        }

        bool JPrimitiveLong::operator==(JObject &other){
            if (other.getClass()!=getClazz()){
                return false;
            }
            JPrimitiveLong* s=dynamic_cast<JPrimitiveLong*>(&other);
            return value==s->value;
        }

        void JPrimitiveLong::set(jlong value){
            this->value=value;
        }

        jlong JPrimitiveLong::get(){
            return value;
        }

        string JPrimitiveLong::toString(){
            stringstream ss;
            ss<<value;
            return ss.str();
        }

        JPrimitiveLong::~JPrimitiveLong(){
        }
    }
}
