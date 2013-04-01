#include "JRunnable.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        class JRunnableClass : public JClass{
          public:
            JRunnableClass():JClass(){
                this->canonicalName="java.lang.Runnable";
                this->name="java.lang.Runnable";
                this->simpleName="Runnable";
                this->bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JRunnable::getClazz(){
            if (clazz==NULL){
                clazz=new JRunnableClass();
            }
            return clazz;
        }

        JRunnable::~JRunnable(){
        }
    }
}
