#include "JObjectInputValidation.h"
#include "JClass.h"

namespace jcpp{
    namespace io{

        class JObjectInputValidationClass : public JClass{
            public:
                JObjectInputValidationClass(){
                    this->canonicalName="java.io.ObjectInputValidation";
                    this->name="java.io.ObjectInputValidation";
                    this->simpleName="ObjectInputValidation";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JObjectInputValidation::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectInputValidationClass();
            }
            return clazz;
        }

        JObjectInputValidation::~JObjectInputValidation(){
        }
    }
}
