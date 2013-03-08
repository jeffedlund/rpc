#include "JDelayed.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JDelayedClass : public JClass{

            public:
              JDelayedClass(){
                  this->canonicalName="java.util.concurrent.Delayed";
                  this->name="java.util.concurrent.Delayed";
                  this->simpleName="Delayed";
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

            JClass* JDelayed::getClazz(){
                if (clazz==NULL){
                    clazz=new JDelayedClass();
                }
                return clazz;
            }

            JDelayed::~JDelayed(){
            }
        }
    }
}

