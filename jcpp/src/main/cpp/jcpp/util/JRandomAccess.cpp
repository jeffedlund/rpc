#include "JRandomAccess.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JRandomAccessClass : public JClass{

        public:
          JRandomAccessClass(){
              this->canonicalName="java.util.RandomAccess";
              this->name="java.util.RandomAccess";
              this->simpleName="RandomAccess";
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JInterface::getClazz();
          }

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JRandomAccess::getClazz(){
            if (clazz==NULL){
                clazz=new JRandomAccessClass();
            }
            return clazz;
        }

        JRandomAccess::~JRandomAccess(){
        }
    }
}


