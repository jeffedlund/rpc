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
                    throw new JInstantiationException("cannot instantiate object of class "+getName());
                }
            };

            static JClass* clazz;

            JClass* JFutureTask::getClazz(){
                if (clazz==NULL){
                    clazz=new JFutureTaskClass();
                }
                return clazz;
            }

            JFutureTask::JFutureTask(JClass* _class):JObject(_class){
                this->callable=NULL;
                this->runnable=NULL;
                this->result=NULL;
                this->bCancel=false;
                this->bDone=false;
            }

            JFutureTask::JFutureTask(JCallable* c):JObject(getClazz()){
                this->callable=c;
                this->runnable=NULL;
                this->result=NULL;
                this->bCancel=false;
                this->bDone=false;
            }

            JFutureTask::JFutureTask(JRunnable* r,JObject* result):JObject(getClazz()){
                this->callable=NULL;
                this->runnable=r;
                this->result=result;
                this->bCancel=false;
                this->bDone=false;
            }

            void JFutureTask::run(){//TODO use mutex
                if (!bCancel){
                    if (callable!=NULL){
                        result=callable->call();
                    }else{
                        runnable->run();
                    }
                }
                bDone=true;
            }

            //TODO use mutex
            bool JFutureTask::cancel(){
                if (bDone){
                    return false;
                }
                this->bCancel=true;
                return true;
            }

            bool JFutureTask::isCancelled(){
                return bCancel;
            }

            bool JFutureTask::isDone(){
                return bDone;
            }

            JObject* JFutureTask::get(){//TODO should block till it is done
                return result;
            }
        }
    }
}
