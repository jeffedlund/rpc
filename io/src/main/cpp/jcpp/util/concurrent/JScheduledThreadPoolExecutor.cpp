
#include "JScheduledThreadPoolExecutor.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledThreadPoolExecutorClass : public JClass{

            public:
                  JScheduledThreadPoolExecutorClass(){
                      this->canonicalName="java.util.concurrent.ScheduledThreadPoolExecutor";
                      this->name="java.util.concurrent.ScheduledThreadPoolExecutor";
                      this->simpleName="ScheduledThreadPoolExecutor";
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
            }

            JScheduledThreadPoolExecutor::JScheduledThreadPoolExecutor(int maxPoolSize,int expiryTimeout):JThreadPoolExecutor(maxPoolSize,expiryTimeout,getClazz()){
            }

            void JScheduledThreadPoolExecutor::execute(JRunnable *command){
                JThreadPoolExecutor::execute(command);
            }

            bool JScheduledThreadPoolExecutor::isShutdown(){
                return JThreadPoolExecutor::isShutdown();
            }

            void JScheduledThreadPoolExecutor::shutdown(){
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
                return NULL;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::schedule(JRunnable* command, jlong delay){
                return NULL;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::scheduleAtFixedRate(JRunnable* command, jlong initialDelay, jlong period){
                return NULL;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::scheduleWithFixedDelay(JRunnable* command, jlong initialDelay, jlong delay){
                return NULL;
            }

            JScheduledThreadPoolExecutor::~JScheduledThreadPoolExecutor(){
            }
        }
    }
}
