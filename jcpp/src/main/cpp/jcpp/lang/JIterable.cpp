#include "JIterable.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        class JIterableClass : public JClass{
          public:
            JIterableClass():JClass(){
                this->canonicalName="java.lang.Iterable";
                this->name="java.lang.Iterable";
                this->simpleName="Iterable";
                this->bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JIterable::getClazz(){
            if (clazz==NULL){
                clazz=new JIterableClass();
            }
            return clazz;
        }

        JIterable::~JIterable(){
        }
    }
}

