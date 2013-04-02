#include "JExecutor.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JExecutorClass : public JClass{

            public:
              JExecutorClass(){
                  this->canonicalName="java.util.concurrent.Executor";
                  this->name="java.util.concurrent.Executor";
                  this->simpleName="Executor";
                  this->bIsInterface=true;
              }

              JClass* getSuperclass(){
                  return JInterface::getClazz();
              }
            };

            static JClass* clazz;

            JClass* JExecutor::getClazz(){
                if (clazz==NULL){
                    clazz=new JExecutorClass();
                }
                return clazz;
            }

            JExecutor::~JExecutor(){
            }
        }
    }
}
