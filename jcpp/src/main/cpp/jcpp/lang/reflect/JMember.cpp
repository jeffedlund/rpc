#include "JMember.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JMemberClass : public JClass{
            public:
                JMemberClass():JClass(JClassLoader::getBootClassLoader()){
                    canonicalName="java.lang.reflect.Member";
                    name="java.lang.reflect.Member";
                    simpleName="Member";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
            };

            static JClass* clazz;

            jint JMember::PUBLIC = 0;

            jint JMember::DECLARED = 1;

            JClass* JMember::getClazz(){
                if (clazz==NULL){
                    clazz= new JMemberClass();
                }
                return clazz;
            }

            JMember::~JMember(){
            }
        }
    }
}
