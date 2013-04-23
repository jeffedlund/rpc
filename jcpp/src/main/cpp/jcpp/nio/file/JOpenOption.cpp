#include "JOpenOption.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JOpenOptionClass : public JClass{
            public:
                JOpenOptionClass(){
                    this->canonicalName="java.nio.file.OpenOption";
                    this->name="java.nio.file.OpenOption";
                    this->simpleName="OpenOption";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JOpenOption::getClazz(){
                if (clazz==NULL){
                    clazz=new JOpenOptionClass();
                }
                return clazz;
            }

            JOpenOption::~JOpenOption(){
            }
        }
    }
}
