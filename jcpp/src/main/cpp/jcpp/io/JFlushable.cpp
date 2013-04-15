#include "JFlushable.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JFlushableClass : public JClass{
            public:
                JFlushableClass(){
                    this->canonicalName="java.io.Flushable";
                    this->name="java.io.Flushable";
                    this->simpleName="Flushable";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFlushable::getClazz(){
            if (clazz==NULL){
                clazz=new JFlushableClass();
            }
            return clazz;
        }

        JFlushable::~JFlushable(){
        }
    }
}
