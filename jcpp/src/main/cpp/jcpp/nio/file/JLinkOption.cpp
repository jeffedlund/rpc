#include "JLinkOption.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            JLinkOption::JLinkOptionClass::JLinkOptionClass(){
                this->canonicalName="java.nio.file.LinkOption";
                this->name="java.nio.file.LinkOption";
                this->simpleName="LinkOption";
                addInterface(JOpenOption::getClazz());
                addInterface(JCopyOption::getClazz());
            }

            void JLinkOption::JLinkOptionClass::fillEnumConstants(){
                addEnumConstant(JLinkOption::NOFOLLOW_LINKS);
            }

            static JClass* clazz;

            JClass* JLinkOption::getClazz(){
                if (clazz==NULL){
                    clazz=new JLinkOptionClass();
                }
                return clazz;
            }

            JLinkOption::JLinkOption(JString* name, JPrimitiveInt* ordinal):JEnum((JEnumClass*)getClazz(),new JString(name),new JPrimitiveInt(ordinal)){
            }

            JLinkOption* JLinkOption::NOFOLLOW_LINKS = new JLinkOption(new JString("NOFOLLOW_LINKS"),new JPrimitiveInt(0));

            JLinkOption::~JLinkOption(){
            }
        }
    }
}
