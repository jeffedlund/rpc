#include "JScheduledFuture.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledFutureClass : public JClass{

            public:
              JScheduledFutureClass(){
                  this->canonicalName="java.util.concurrent.ScheduledFuture";
                  this->name="java.util.concurrent.ScheduledFuture";
                  this->simpleName="ScheduledFuture";
                  this->bIsInterface=true;
              }

              JClass* getSuperclass(){
                  return JFuture::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };

            static JClass* clazz;

            JClass* JScheduledFuture::getClazz(){
                if (clazz==NULL){
                    clazz=new JScheduledFutureClass();
                }
                return clazz;
            }
        }
    }
}
