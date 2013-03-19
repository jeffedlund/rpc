#include "JListIterator.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JListIteratorClass : public JClass{

        public:
          JListIteratorClass(){
              this->canonicalName="java.util.ListIterator";
              this->name="java.util.ListIterator";
              this->simpleName="ListIterator";
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JIterator::getClazz();
          }

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JListIterator::getClazz(){
            if (clazz==NULL){
                clazz=new JListIteratorClass();
            }
            return clazz;
        }

        JListIterator::~JListIterator(){
        }
    }
}


