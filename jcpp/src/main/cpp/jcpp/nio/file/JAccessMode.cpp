#include "JAccessMode.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            JAccessMode::JAccessModeClass::JAccessModeClass():JEnumClass(){
                this->canonicalName="java.nio.file.AccessMode";
                this->name="java.nio.file.AccessMode";
                this->simpleName="AccessMode";
            }

            JClass* JAccessMode::JAccessModeClass::getSuperclass(){
                return JEnum::getClazz();
            }

            void JAccessMode::JAccessModeClass::fillEnumConstants(){
                addEnumConstant(JAccessMode::READ);
                addEnumConstant(JAccessMode::WRITE);
                addEnumConstant(JAccessMode::EXECUTE);
            }

            static JClass* clazz;
            JClass* JAccessMode::getClazz(){
                if (clazz==NULL){
                    clazz=new JAccessModeClass();
                }
                return clazz;
            }

            JAccessMode::JAccessMode(JString* name, JPrimitiveInt* ordinal):JEnum((JEnumClass*)getClazz(),name,ordinal){
            }

            JAccessMode* JAccessMode::READ = new JAccessMode(new JString("READ"),new JPrimitiveInt(0));

            JAccessMode* JAccessMode::WRITE = new JAccessMode(new JString("WRITE"),new JPrimitiveInt(1));

            JAccessMode* JAccessMode::EXECUTE = new JAccessMode(new JString("EXECUTE"),new JPrimitiveInt(2));

            JAccessMode::~JAccessMode(){
            }
        }
    }
}
