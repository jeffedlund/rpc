#include "JComparable.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        class JComparableClass : public JClass{
          public:
            JComparableClass():JClass(){
                this->canonicalName="java.lang.Comparable";
                this->name="java.lang.Comparable";
                this->simpleName="Comparable";
                this->bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JComparable::getClazz(){
            if (clazz==NULL){
                clazz=new JComparableClass();
            }
            return clazz;
        }

        JComparable::~JComparable(){
        }
    }
}

