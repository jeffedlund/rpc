#include "JScheduledFutureTask.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledFutureTaskClass : public JClass{

            public:
              JScheduledFutureTaskClass(){
                  this->canonicalName="java.util.concurrent.ScheduledFutureTask";
                  this->name="java.util.concurrent.ScheduledFutureTask";
                  this->simpleName="ScheduledFutureTask";
                  addInterface(JRunnableScheduledFuture::getClazz());
              }

              JClass* getSuperclass(){
                  return JTimerTask::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };

            static JClass* clazz;

            JClass* JScheduledFutureTask::getClazz(){
                if (clazz==NULL){
                    clazz=new JScheduledFutureTaskClass();
                }
                return clazz;
            }

            JScheduledFutureTask::JScheduledFutureTask(JCallable* c,long initialDelay, jlong period):JTimerTask(getClazz()){
                this->callable=c;
                this->runnable=NULL;
                this->result=NULL;
                this->initialDelay=initialDelay;
                this->period=period;
            }

            JScheduledFutureTask::JScheduledFutureTask(JRunnable* r,JObject* result,long initialDelay, jlong period):JTimerTask(getClazz()){
                this->callable=NULL;
                this->runnable=r;
                this->result=result;
                this->initialDelay=initialDelay;
                this->period=period;
            }

            void JScheduledFutureTask::run(){
                if (callable!=NULL){
                    result=callable->call();
                }else{
                    runnable->run();
                }
            }

            bool JScheduledFutureTask::cancel(){
                this->bCancel=true;
            }

            bool JScheduledFutureTask::isCancelled(){
                return bCancel;
            }

            bool JScheduledFutureTask::isDone(){

            }

            JObject* JScheduledFutureTask::get(){
            }

            bool JScheduledFutureTask::isPeriodic(){
                return period!=0;
            }

            jlong JScheduledFutureTask::getDelay(){
                return initialDelay;
            }

            long JScheduledFutureTask::getPeriod(){
                return period;
            }
        }
    }
}

