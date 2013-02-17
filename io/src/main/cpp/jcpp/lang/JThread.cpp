#include "JThread.h"
#include "JRunnable.h"
#include "JInstantiationException.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JThreadClass : public JClass{
          public:
            JThreadClass():JClass(){
                this->canonicalName="java.lang.Thread";
                this->name="java.lang.Thread";
                this->simpleName="Thread";
                addInterface(JRunnable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of class "+getName());
            }
        };

        static JClass* clazz;

        JClass* JThread::getClazz(){
            if (clazz==NULL){
                clazz=new JThreadClass();
            }
            return clazz;
        }

        JThread::JThread(QThread* thread):JObject(getClazz()){
            this->thread=thread;
            this->deletable=false;
        }

        JThread::JThread():JObject(getClazz()){
            this->thread=new JQThread(this);
            this->deletable=true;
        }

        JThread::JThread(JRunnable* runnable):JObject(getClazz()){
            this->runnable=runnable;
            this->thread=new JQThread(runnable);
        }

        QObject* JThread::getQObject(){
            return thread;
        }

        void JThread::move(QObjectAware* oa){
            QObject* o=oa->getQObject();
            o->moveToThread(thread);
        }

        JThread* JThread::currentThread(){
            return new JThread(QThread::currentThread());
        }

        void JThread::sleep(jlong s){
            JQThread::extSleep(s);
        }

        void JThread::run(){
            if (runnable!=NULL){
                runnable->run();;
            }
        }

        void JThread::start(){
            thread->start();
        }

        string JThread::toString(){
            return "TODO";
        }

        JThread::~JThread(){
            if (deletable){
                delete thread;
            }
        }
    }
}
