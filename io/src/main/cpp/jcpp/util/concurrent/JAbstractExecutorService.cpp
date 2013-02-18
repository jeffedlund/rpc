
#include "JAbstractExecutorService.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JAbstractExecutorServiceClass : public JClass{

            public:
              JAbstractExecutorServiceClass(){
                  this->canonicalName="java.util.concurrent.AbstractExecutorService";
                  this->name="java.util.concurrent.AbstractExecutorService";
                  this->simpleName="AbstractExecutorService";
                  this->serialVersionUID=0;
                  addInterface(JExecutorService::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };

            static JClass* clazz;

            JClass* JAbstractExecutorService::getClazz(){
                if (clazz==NULL){
                    clazz=new JAbstractExecutorServiceClass();
                }
                return clazz;
            }

            JAbstractExecutorService::JAbstractExecutorService(JClass* _class):JObject(_class){
            }

            JRunnableFuture* JAbstractExecutorService::newTaskFor(JRunnable* runnable, JObject* result){
                return new JFutureTask(runnable, result);
            }

            JRunnableFuture* JAbstractExecutorService::newTaskFor(JCallable* callable){
                return new JFutureTask(callable);
            }

            JFuture* JAbstractExecutorService::submit(JRunnable* task) {
                JRunnableFuture* ftask = newTaskFor(task, NULL);
                execute(ftask);
                return ftask;
            }

            JFuture* JAbstractExecutorService::submit(JRunnable* task, JObject* result) {
                JRunnableFuture* ftask = newTaskFor(task, result);
                execute(ftask);
                return ftask;
            }

            JFuture* JAbstractExecutorService::submit(JCallable* task) {
                JRunnableFuture* ftask = newTaskFor(task);
                execute(ftask);
                return ftask;
            }
        }
    }
}
