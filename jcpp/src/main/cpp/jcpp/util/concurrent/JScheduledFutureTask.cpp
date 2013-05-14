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
            };

            static JClass* clazz;

            JClass* JScheduledFutureTask::getClazz(){
                if (clazz==NULL){
                    clazz=new JScheduledFutureTaskClass();
                }
                return clazz;
            }

            JScheduledFutureTask::JScheduledFutureTask(JCallable* c,jlong initialDelay, jlong period):JTimerTask(getClazz()){
                this->callable=c;
                this->runnable=NULL;
                this->initialResult=NULL;
                this->result=NULL;
                this->initialDelay=initialDelay;
                this->period=period;
            }

            JScheduledFutureTask::JScheduledFutureTask(JRunnable* r,JObject* result,jlong initialDelay, jlong period):JTimerTask(getClazz()){
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

            jbool JScheduledFutureTask::cancel(){
                jbool b=false;
                lock();
                if ((period<=0 && !bDone) || period>0){
                    JTimerTask::cancel();
                    b=true;
                }
                unlock();
                return b;
            }

            jbool JScheduledFutureTask::isCancelled(){
                return JTimerTask::isCancelled();
            }

            jbool JScheduledFutureTask::isDone(){
                jbool b;
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

            jbool JScheduledFutureTask::isPeriodic(){
                return period!=0;
            }

            jlong JScheduledFutureTask::getDelay(){
                return initialDelay;
            }

            jlong JScheduledFutureTask::getPeriod(){
                return period;
            }

            JScheduledFutureTask::~JScheduledFutureTask(){
            }
        }
    }
}

