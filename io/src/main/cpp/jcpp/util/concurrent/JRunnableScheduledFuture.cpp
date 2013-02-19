#include "JRunnableScheduledFuture.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JRunnableScheduledFutureClass : public JClass{

            public:
              JRunnableScheduledFutureClass(){
                  this->canonicalName="java.util.concurrent.RunnableScheduledFuture";
                  this->name="java.util.concurrent.RunnableScheduledFuture";
                  this->simpleName="RunnableScheduledFuture";
                  this->bIsInterface=true;
                  addInterface(JRunnableFuture::getClazz());
                  addInterface(JScheduledFuture::getClazz());
              }

              JClass* getSuperclass(){
                  return JInterface::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };

            static JClass* clazz;

            JClass* JRunnableScheduledFuture::getClazz(){
                if (clazz==NULL){
                    clazz=new JRunnableScheduledFutureClass();
                }
                return clazz;
            }
        }
    }
}

