
#include "JThreadPoolExecutor.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JQRunnable : public QRunnable{
            protected:
                JRunnable* runnable;
            public:
                JQRunnable(JRunnable* runnable){
                    this->runnable=runnable;
                    setAutoDelete(true);
                }

                void run(){
                    try{
                        runnable->run();
                    }catch(JThrowable* th){
                        th->printStackTrace(&cout);//TODO call JUncaughtExceptionHandler
                    }
                }
            };

            class JThreadPoolExecutorClass : public JClass{

            public:
                  JThreadPoolExecutorClass(){
                      this->canonicalName="java.util.concurrent.ThreadPoolExecutor";
                      this->name="java.util.concurrent.ThreadPoolExecutor";
                      this->simpleName="ThreadPoolExecutor";
                  }

                  JClass* getSuperclass(){
                      return JAbstractExecutorService::getClazz();
                  }

                  JObject* newInstance(){
                      throw new JThreadPoolExecutor();
                  }
            };

            static JClass* clazz;

            JClass* JThreadPoolExecutor::getClazz(){
                if (clazz==NULL){
                    clazz=new JThreadPoolExecutorClass();
                }
                return clazz;
            }

            JThreadPoolExecutor::JThreadPoolExecutor(jint maxPoolSize,jint expiryTimeout,JClass* _class):JAbstractExecutorService(_class){
                this->threadPool=new QThreadPool();
                threadPool->setMaxThreadCount(maxPoolSize);
                threadPool->setExpiryTimeout(expiryTimeout);
                this->bShutdown=false;
            }

            JThreadPoolExecutor::JThreadPoolExecutor():JAbstractExecutorService(getClazz()){
                this->threadPool=new QThreadPool();
                threadPool->setMaxThreadCount(10);
                threadPool->setExpiryTimeout(60000);
                this->bShutdown=false;
            }

            JThreadPoolExecutor::JThreadPoolExecutor(jint maxPoolSize,jint expiryTimeout):JAbstractExecutorService(getClazz()){
                this->threadPool=new QThreadPool();
                threadPool->setMaxThreadCount(maxPoolSize);
                threadPool->setExpiryTimeout(expiryTimeout);
                this->bShutdown=false;
            }

            void JThreadPoolExecutor::execute(JRunnable *command){
                if (!bShutdown){
                    threadPool->start(new JQRunnable(command));
                }
            }

            jbool JThreadPoolExecutor::isShutdown(){
                return bShutdown;
            }

            void JThreadPoolExecutor::shutdown(){
                if (!bShutdown){
                    bShutdown=true;
                    threadPool->waitForDone();
                }
            }

            JThreadPoolExecutor::~JThreadPoolExecutor(){
                delete threadPool;
            }
        }
    }
}
