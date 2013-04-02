#include "JComparator.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JComparatorClass : public JClass{

        public:
          JComparatorClass(){
              this->canonicalName="java.util.Comparator";
              this->name="java.util.Comparator";
              this->simpleName="Comparator";
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JInterface::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JComparator::getClazz(){
            if (clazz==NULL){
                clazz=new JComparatorClass();
            }
            return clazz;
        }

        JComparator::~JComparator(){
        }
    }
}


