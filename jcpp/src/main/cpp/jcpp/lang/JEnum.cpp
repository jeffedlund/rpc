#include "JEnum.h"
#include "JClass.h"
#include "JClassCastException.h"

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

        JString* JEnum::getName(){
            return name;
        }

        JPrimitiveInt* JEnum::getOrdinal(){
            return ordinal;
        }

        jint JEnum::compareTo(JObject* o){
            JEnum* e=dynamic_cast<JEnum*>(o);
            if (getClass() != e->getClass()){//TODO implement && this->getgetDeclaringClass() != other.getDeclaringClass())
                throw new JClassCastException();
            }
            return ordinal - e->getOrdinal();
        }

        jbool JEnum::equals(JObject* other){
            if (other->getClass()==getClass()){
                JEnum* s=dynamic_cast<JEnum*>(other);
                return (*name)==(*s->name) && (*ordinal)==(*s->ordinal);
            }
            return false;
        }

        jint JEnum::hashCode(){
            return JObject::hashCode();
        }

        JString JEnum::toString(){
            return name->toString();
        }

        JEnum::~JEnum() {
            delete name;
            delete ordinal;
        }
    }
}
