#include "JEnumeration.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JEnumerationClass : public JClass{

        public:
          JEnumerationClass(){
              this->canonicalName="java.util.Enumeration";
              this->name="java.util.Enumeration";
              this->simpleName="Enumeration";
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

        JClass* JEnumeration::getClazz(){
            if (clazz==NULL){
                clazz=new JEnumerationClass();
            }
            return clazz;
        }

        JEnumeration::~JEnumeration(){
        }
    }
}


