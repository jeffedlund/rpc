#include "JFutureTask.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JFutureTaskClass : public JClass{

            public:
              JFutureTaskClass(){
                  this->canonicalName="java.util.concurrent.FutureTask";
                  this->name="java.util.concurrent.FutureTask";
                  this->simpleName="FutureTask";
                  addInterface(JRunnableFuture::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              JObject* newInstance(){
                  return new JFutureTask();
              }
            };

            static JClass* clazz;

            JClass* JFutureTask::getClazz(){
                if (clazz==NULL){
                    clazz=new JFutureTaskClass();
                }
                return clazz;
            }

            JFutureTask::JFutureTask():JObject(getClazz()){
                this->callable=NULL;
                this->runnable=NULL;
                this->result=NULL;
            }

            JFutureTask::JFutureTask(JCallable* c):JObject(getClazz()){
                this->callable=c;
            }

            JFutureTask::JFutureTask(JRunnable* r,JObject* result):JObject(getClazz()){
                this->runnable=r;
                this->result=result;
            }

            void JFutureTask::run(){
                if (callable!=NULL){
                    result=callable->call();
                }else{
                    runnable->run();
                }
            }


            bool JFutureTask::cancel(){
                return false;//TODO
            }

            bool JFutureTask::isCancelled(){
                return false;//TODO
            }

            bool JFutureTask::isDone(){
                return false;//TODO
            }

            JObject* JFutureTask::get(){
                return result;
            }
        }
    }
}

