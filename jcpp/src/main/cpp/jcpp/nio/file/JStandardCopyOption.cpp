#include "JStandardCopyOption.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            JStandardCopyOption::JStandardCopyOptionClass::JStandardCopyOptionClass(){
                this->canonicalName="java.nio.file.StandardCopyOption";
                this->name="java.nio.file.StandardCopyOption";
                this->simpleName="StandardCopyOption";
                this->serialVersionUID=0ULL;
                addInterface(JCopyOption::getClazz());
            }

            void JStandardCopyOption::JStandardCopyOptionClass::fillEnumConstants(){
                addEnumConstant(JStandardCopyOption::REPLACE_EXISTING);
                addEnumConstant(JStandardCopyOption::COPY_ATTRIBUTES);
                addEnumConstant(JStandardCopyOption::ATOMIC_MOVE);
            }

            static JClass* clazz;

            JClass* JStandardCopyOption::getClazz(){
                if (clazz==NULL){
                    clazz=new JStandardCopyOptionClass();
                }
                return clazz;
            }

            JStandardCopyOption::JStandardCopyOption(JString* name, JPrimitiveInt* ordinal):JEnum((JEnumClass*)getClazz(),name,ordinal){
            }


            JStandardCopyOption* JStandardCopyOption::REPLACE_EXISTING = new JStandardCopyOption(new JString("REPLACE_EXISTING"),new JPrimitiveInt(0));

            JStandardCopyOption* JStandardCopyOption::COPY_ATTRIBUTES = new JStandardCopyOption(new JString("COPY_ATTRIBUTES"),new JPrimitiveInt(1));

            JStandardCopyOption* JStandardCopyOption::ATOMIC_MOVE = new JStandardCopyOption(new JString("ATOMIC_MOVE"),new JPrimitiveInt(2));

            JStandardCopyOption::~JStandardCopyOption(){
            }
        }
    }
}
