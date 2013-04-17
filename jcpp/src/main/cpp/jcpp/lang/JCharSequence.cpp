#include "JCharSequence.h"
#include "JClass.h"

namespace jcpp{
    namespace lang{
        class JCharSequenceClass : public JClass{
            public:
                JCharSequenceClass(){
                    this->canonicalName="java.lang.CharSequence";
                    this->name="java.lang.CharSequence";
                    this->simpleName="CharSequence";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JCharSequence::getClazz(){
            if (clazz==NULL){
                clazz=new JCharSequenceClass();
            }
            return clazz;
        }

        JCharSequence::~JCharSequence(){
        }
    }
}
