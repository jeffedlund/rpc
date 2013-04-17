#include "JAppendable.h"
#include "JClass.h"

namespace jcpp{
    namespace lang{
        class JAppendableClass : public JClass{
            public:
                JAppendableClass(){
                    this->canonicalName="java.lang.Appendable";
                    this->name="java.lang.Appendable";
                    this->simpleName="Appendable";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JAppendable::getClazz(){
            if (clazz==NULL){
                clazz=new JAppendableClass();
            }
            return clazz;
        }

        JAppendable::~JAppendable(){
        }
    }
}
