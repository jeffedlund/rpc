#include "JPrimitiveLong.h"
#include "JClass.h"
#include <vector>
#include <iostream>
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
                addInterface(JComparable::getClazz());
                addInterface(JSerializable::getClazz());
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

        jint JPrimitiveLong::compareTo(JObject* o){
            JPrimitiveLong* s=dynamic_cast<JPrimitiveLong*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveLong::equals(JObject* other){
            if (other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveLong* s=dynamic_cast<JPrimitiveLong*>(other);
            return value==s->value;
        }

        JPrimitiveLong& JPrimitiveLong::operator+=(jlong f){
            value+=f;
            return *this;
        }

        JPrimitiveLong& JPrimitiveLong::operator-=(jlong f){
            value-=f;
            return *this;
        }

        JPrimitiveLong& JPrimitiveLong::operator*=(jlong f){
            value*=f;
            return *this;
        }

        void JPrimitiveLong::set(jlong value){
            this->value=value;
        }

        jlong JPrimitiveLong::get(){
            return value;
        }

        jint JPrimitiveLong::hashCode(){
            return (jint)value;
        }

        JString JPrimitiveLong::toString(){
            JString ss;
            ss<<value;
            return ss;
        }

        JPrimitiveLong::~JPrimitiveLong(){
        }
    }
}
