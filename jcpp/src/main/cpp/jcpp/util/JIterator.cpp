#include "JIterator.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JIteratorClass : public JClass{

        public:
          JIteratorClass(){
              this->canonicalName="java.util.Iterator";
              this->name="java.util.Iterator";
              this->simpleName="Iterator";
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

        JClass* JIterator::getClazz(){
            if (clazz==NULL){
                clazz=new JIteratorClass();
            }
            return clazz;
        }

        JIterator::~JIterator(){
        }
    }
}

