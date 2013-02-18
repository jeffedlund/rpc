
#include "JRunnableFuture.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JRunnableFutureClass : public JClass{

            public:
              JRunnableFutureClass(){
                  this->canonicalName="java.util.concurrent.RunnableFuture";
                  this->name="java.util.concurrent.RunnableFuture";
                  this->simpleName="RunnableFuture";
                  this->bIsInterface=true;
                  addInterface(JRunnable::getClazz());
                  addInterface(JFuture::getClazz());
              }

              JClass* getSuperclass(){
                  return JInterface::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };

            static JClass* clazz;

            JClass* JRunnableFuture::getClazz(){
                if (clazz==NULL){
                    clazz=new JRunnableFutureClass();
                }
                return clazz;
            }
        }
    }
}
