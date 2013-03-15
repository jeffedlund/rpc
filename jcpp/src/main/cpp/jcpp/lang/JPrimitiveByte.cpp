#include "JPrimitiveByte.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveByteClass : public JClass{
          public:
            JPrimitiveByteClass(){
                this->canonicalName="byte";
                this->name="byte";
                this->simpleName="byte";
                this->bIsPrimitive=true;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JPrimitiveByte(0);
            }
        };

        static JClass* clazz;

        JClass* JPrimitiveByte::getClazz(){
            if (clazz==NULL){
                clazz=new JPrimitiveByteClass();
            }
            return clazz;
        }

        JPrimitiveByte::JPrimitiveByte(jbyte value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveByte::JPrimitiveByte():JObject(getClazz()){
            this->value=0;
        }

        bool JPrimitiveByte::operator==(JObject &other){
            if (other.getClass()!=getClazz()){
                return false;
            }
            JPrimitiveByte* s=dynamic_cast<JPrimitiveByte*>(&other);
            return value==s->value;
        }

        JPrimitiveByte JPrimitiveByte::operator+=(jbyte f){
            value+=f;
            return *this;
        }

        JPrimitiveByte JPrimitiveByte::operator-=(jbyte f){
            value-=f;
            return *this;
        }

        JPrimitiveByte JPrimitiveByte::operator*=(jbyte f){
            value*=f;
            return *this;
        }

        void JPrimitiveByte::set(jbyte value){
            this->value=value;
        }

        jbyte JPrimitiveByte::get(){
            return value;
        }

        string JPrimitiveByte::toString(){
            stringstream ss;
            ss<<value;//TODO not extra!
            return ss.str();
        }

        JPrimitiveByte::~JPrimitiveByte(){
        }
    }
}
