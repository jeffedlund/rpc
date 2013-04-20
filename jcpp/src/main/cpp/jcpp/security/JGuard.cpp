#include "JGuard.h"
#include "JClass.h"

namespace jcpp{
    namespace security{
        class JGuardClass : public JClass{
            public:
                JGuardClass(){
                    this->canonicalName="java.security.Guard";
                    this->name="java.security.Guard";
                    this->simpleName="Guard";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JGuard::getClazz(){
            if (clazz==NULL){
                clazz=new JGuardClass();
            }
            return clazz;
        }

        JGuard::~JGuard(){
        }
    }
}
