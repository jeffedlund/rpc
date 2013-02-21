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
                this->initialResult=NULL;
                this->result=NULL;
                this->initialDelay=initialDelay;
                this->period=period;
            }

            JScheduledFutureTask::JScheduledFutureTask(JRunnable* r,JObject* result,long initialDelay, jlong period):JTimerTask(getClazz()){
                this->callable=NULL;
                this->runnable=r;
                this->initialResult=result;
                this->result=NULL;
                this->initialDelay=initialDelay;
                this->period=period;
            }

            void JScheduledFutureTask::run(){
                if (!JTimerTask::isCancelled()){
                    if (!isPeriodic() && isDone()){
                        return;
                    }

                    //reset it to not done
                    lock();
                    bDone=false;
                    unlock();

                    JObject* r=NULL;
                    if (callable!=NULL){
                        r=callable->call();
                    }else{
                        runnable->run();
                        r=this->initialResult;
                    }
                    setResult(r);
                }
            }

            bool JScheduledFutureTask::cancel(){
                bool b=false;
                lock();
                if ((period<=0 && !bDone) || period>0){
                    JTimerTask::cancel();
                    b=true;
                }
                unlock();
                return b;
            }

            bool JScheduledFutureTask::isCancelled(){
                return JTimerTask::isCancelled();
            }

            bool JScheduledFutureTask::isDone(){
                bool b;
                lock();
                b=bDone;
                unlock();
                return b;
            }

            void JScheduledFutureTask::setResult(JObject* result){
                lock();
                this->result=result;
                bDone=true;
                notifyAll();
                unlock();
            }


            JObject* JScheduledFutureTask::get(){
                JObject* r=NULL;
                lock();
                while (!bDone && !isCancelled()){
                    wait();
                }
                if (bDone){
                    r=this->result;
                }//TODO else throw cancelexeption stuff
                unlock();
                return r;
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

