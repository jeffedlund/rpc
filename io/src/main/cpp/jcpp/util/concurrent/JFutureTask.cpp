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

            void JFutureTask::run(){
                JObject* r=NULL;
                if (!isCancelled()){
                    if (callable!=NULL){
                        r=callable->call();
                    }else{
                        runnable->run();
                        r=this->result;
                    }
                    setResult(r);
                }
            }

            bool JFutureTask::cancel(){//TODO not ideal, should call threadpool to avoid running it
                bool r=false;
                lock();
                if (!bDone){
                    this->bCancel=true;
                    r=true;
                }
                unlock();
                return r;
            }

            bool JFutureTask::isCancelled(){
                bool b;
                lock();
                b=this->bCancel;
                unlock();
                return b;
            }

            bool JFutureTask::isDone(){
                bool b;
                lock();
                b=bDone;
                unlock();
                return b;
            }

            void JFutureTask::setResult(JObject* result){
                lock();
                this->result=result;
                bDone=true;
                notifyAll();
                unlock();
            }

            JObject* JFutureTask::get(){
                JObject* r=NULL;
                lock();
                while (!bDone && !bCancel){
                    wait();
                }
                if (bDone){
                    r=this->result;
                }//TODO else throw cancelexeption stuff
                unlock();
                return r;
            }
        }
    }
}
