#include "JExecutorService.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JExecutorServiceClass : public JClass{

            public:
              JExecutorServiceClass(){
                  this->canonicalName="java.util.concurrent.ExecutorService";
                  this->name="java.util.concurrent.ExecutorService";
                  this->simpleName="ExecutorService";
                  this->bIsInterface=true;
                  addInterface(JExecutor::getClazz());
              }

              JClass* getSuperclass(){
                  return JInterface::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };

            static JClass* clazz;

            JClass* JExecutorService::getClazz(){
                if (clazz==NULL){
                    clazz=new JExecutorServiceClass();
                }
                return clazz;
            }
        }
    }
}
