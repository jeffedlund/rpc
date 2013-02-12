#include "JEnum.h"
#include "JClass.h"

namespace jcpp{
    namespace lang{
        JEnum::JEnum(JEnumClass* _class,JString* name,JPrimitiveInt* ordinal):JObject(_class){
            this->name=name;
            this->ordinal=ordinal;
        }

        static JClass* clazz;

        JClass* JEnum::getClazz(){
            if (clazz==NULL){
                clazz=new JEnumClass();
            }
            return clazz;
        }

        bool JEnum::operator==(JObject &other){
            if (other.getClass()==getClazz()){
                JEnum* s=dynamic_cast<JEnum*>(&other);
                return (*name)==(*s->name) && (*ordinal)==(*s->ordinal);
            }
            return false;
        }

        JString* JEnum::getName(){
            return name;
        }

        JPrimitiveInt* JEnum::getOrdinal(){
            return ordinal;
        }

        string JEnum::toString(){
            return name->toString();
        }

        JEnum::~JEnum() {
            delete name;
            delete ordinal;
        }
    }
}
