#include "JCallable.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCallableClass : public JClass{

            public:
              JCallableClass(){
                  this->canonicalName="java.util.concurrent.Callable";
                  this->name="java.util.concurrent.Callable";
                  this->simpleName="Callable";
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

            JClass* JCallable::getClazz(){
                if (clazz==NULL){
                    clazz=new JCallableClass();
                }
                return clazz;
            }

            JCallable::~JCallable(){
            }
        }
    }
}
