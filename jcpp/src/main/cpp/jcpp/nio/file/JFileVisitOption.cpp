#include "JFileVisitOption.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            JFileVisitOption::JFileVisitOptionClass::JFileVisitOptionClass():JEnumClass(){
                this->canonicalName="java.nio.file.FileVisitOption";
                this->name="java.nio.file.FileVisitOption";
                this->simpleName="FileVisitOption";
            }

            void JFileVisitOption::JFileVisitOptionClass::fillEnumConstants(){
                addEnumConstant(JFileVisitOption::FOLLOW_LINKS);
            }

            static JClass* clazz;

            JClass* JFileVisitOption::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileVisitOptionClass();
                }
                return clazz;
            }

            JFileVisitOption::JFileVisitOption(JString* name, JPrimitiveInt* ordinal):JEnum((JEnumClass*)getClazz(),name,ordinal){
            }

            JFileVisitOption* JFileVisitOption::FOLLOW_LINKS = new JFileVisitOption(new JString("FOLLOW_LINKS"),new JPrimitiveInt(0));

            JFileVisitOption::~JFileVisitOption(){
            }
        }
    }
}
