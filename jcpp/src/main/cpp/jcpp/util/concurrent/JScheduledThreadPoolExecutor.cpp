#include "JScheduledThreadPoolExecutor.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>
#include "JScheduledFutureTask.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledThreadPoolExecutorClass : public JClass{

            public:
                  JScheduledThreadPoolExecutorClass(){
                      this->canonicalName="java.util.concurrent.ScheduledThreadPoolExecutor";
                      this->name="java.util.concurrent.ScheduledThreadPoolExecutor";
                      this->simpleName="ScheduledThreadPoolExecutor";
                      addInterface(JScheduledExecutorService::getClazz());
                  }

                  JClass* getSuperclass(){
                      return JThreadPoolExecutor::getClazz();
                  }

                  JObject* newInstance(){
                      throw new JScheduledThreadPoolExecutor();
                  }
            };

            static JClass* clazz;

            JClass* JScheduledThreadPoolExecutor::getClazz(){
                if (clazz==NULL){
                    clazz=new JScheduledThreadPoolExecutorClass();
                }
                return clazz;
            }

            JScheduledThreadPoolExecutor::JScheduledThreadPoolExecutor():JThreadPoolExecutor(10,60000,getClazz()){//TODO use static int
                timer=new JTimer();
            }

            JScheduledThreadPoolExecutor::JScheduledThreadPoolExecutor(jint maxPoolSize,jint expiryTimeout):JThreadPoolExecutor(maxPoolSize,expiryTimeout,getClazz()){
                timer=new JTimer();
            }

            void JScheduledThreadPoolExecutor::execute(JRunnable *command){
                JThreadPoolExecutor::execute(command);
            }

            jbool JScheduledThreadPoolExecutor::isShutdown(){
                return JThreadPoolExecutor::isShutdown();
            }

            void JScheduledThreadPoolExecutor::shutdown(){
                timer->cancel();
                JThreadPoolExecutor::shutdown();
            }

            JFuture* JScheduledThreadPoolExecutor::submit(JRunnable* task){
                return JThreadPoolExecutor::submit(task);
            }

            JFuture* JScheduledThreadPoolExecutor::submit(JRunnable* task, JObject* result){
                return JThreadPoolExecutor::submit(task,result);
            }

            JFuture* JScheduledThreadPoolExecutor::submit(JCallable* task){
                return JThreadPoolExecutor::submit(task);
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::schedule(JCallable* callable, jlong delay){
                JScheduledFutureTask* scheduledFutureTask=new JScheduledFutureTask(callable,delay,0);
                timer->schedule(scheduledFutureTask,delay,0);
                return scheduledFutureTask;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::schedule(JRunnable* command, jlong delay){
                JScheduledFutureTask* scheduledFutureTask=new JScheduledFutureTask(command,NULL,delay,0);
                timer->schedule(scheduledFutureTask,delay,0);
                return scheduledFutureTask;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::schedule(JRunnable* command, jlong initialDelay, jlong period){
                JScheduledFutureTask* scheduledFutureTask=new JScheduledFutureTask(command,NULL,initialDelay,period);
                timer->schedule(scheduledFutureTask,initialDelay,period);
                return scheduledFutureTask;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::schedule(JCallable* callable, jlong initialDelay, jlong period){
                JScheduledFutureTask* scheduledFutureTask=new JScheduledFutureTask(callable,initialDelay,period);
                timer->schedule(scheduledFutureTask,initialDelay,period);
                return scheduledFutureTask;
            }

            JScheduledThreadPoolExecutor::~JScheduledThreadPoolExecutor(){
                delete timer;
            }
        }
    }
}
