#include "JCopyOption.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JCopyOptionClass : public JClass{
            public:
                JCopyOptionClass(){
                    this->canonicalName="java.nio.file.CopyOption";
                    this->name="java.nio.file.CopyOption";
                    this->simpleName="CopyOption";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JCopyOption::getClazz(){
                if (clazz==NULL){
                    clazz=new JCopyOptionClass();
                }
                return clazz;
            }

            JCopyOption::~JCopyOption(){
            }
        }
    }
}
