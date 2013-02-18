
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
                    runnable->run();
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

            JThreadPoolExecutor::JThreadPoolExecutor(int maxPoolSize,int expiryTimeout,JClass* _class):JAbstractExecutorService(_class){
                this->threadPool=new QThreadPool();
                threadPool->setMaxThreadCount(maxPoolSize);
                threadPool->setExpiryTimeout(expiryTimeout);
            }

            JThreadPoolExecutor::JThreadPoolExecutor():JAbstractExecutorService(getClazz()){
                this->threadPool=new QThreadPool();
                threadPool->setMaxThreadCount(10);
                threadPool->setExpiryTimeout(60000);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(int maxPoolSize,int expiryTimeout):JAbstractExecutorService(getClazz()){
                this->threadPool=new QThreadPool();
                threadPool->setMaxThreadCount(maxPoolSize);
                threadPool->setExpiryTimeout(expiryTimeout);
            }

            void JThreadPoolExecutor::execute(JRunnable *command){
                threadPool->start(new JQRunnable(command));
            }

            bool JThreadPoolExecutor::isShutdown(){
                return false;//TODO?
            }

            void JThreadPoolExecutor::shutdown(){
                threadPool->waitForDone();
            }

            JThreadPoolExecutor::~JThreadPoolExecutor(){
                delete threadPool;
            }
        }
    }
}
