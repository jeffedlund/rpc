#include "JScheduledExecutorService.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledExecutorServiceClass : public JClass{

            public:
              JScheduledExecutorServiceClass(){
                  this->canonicalName="java.util.concurrent.ScheduledExecutorService";
                  this->name="java.util.concurrent.ScheduledExecutorService";
                  this->simpleName="ScheduledExecutorService";
                  this->bIsInterface=true;
                  addInterface(JExecutorService::getClazz());
              }

              JClass* getSuperclass(){
                  return JExecutorService::getClazz();
              }
            };

            static JClass* clazz;

            JClass* JScheduledExecutorService::getClazz(){
                if (clazz==NULL){
                    clazz=new JScheduledExecutorServiceClass();
                }
                return clazz;
            }

            JScheduledExecutorService::~JScheduledExecutorService(){
            }
        }
    }
}
