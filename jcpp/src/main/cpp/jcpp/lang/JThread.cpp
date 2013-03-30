#include "JThread.h"
#include "JRunnable.h"
#include "JInstantiationException.h"
#include <QCoreApplication>
#include "Collections.h"
#include "QObjectHolder.h"
#include "JIdentityHashMap.h"
using namespace std;
using namespace jcpp::util;

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
        };

        static JClass* clazz;

        JClass* JThread::getClazz(){
            if (clazz==NULL){
                clazz=new JThreadClass();
            }
            return clazz;
        }

        static JThreadLocal lockedObjects;

        jbool JThread::addObjectLocked(JObject* o){
            JIdentityHashMap* m=(JIdentityHashMap*)lockedObjects.get();
            if (m==NULL){
                m=new JIdentityHashMap();
                lockedObjects.set(m);
            }
            JInteger* i=(JInteger*)m->get(o);
            if (i==NULL){
                i=new JInteger(0);
                m->put(o,i);
            }
            i->set(i->get()+1);
            return i->get()==1;
        }

        jbool JThread::removeObjectLocked(JObject* o){
            bool b=false;
            JIdentityHashMap* m=(JIdentityHashMap*)lockedObjects.get();
            if (m!=NULL){
                JInteger* i=(JInteger*)m->get(o);
                if (i!=NULL){
                    i->set(i->get()-1);
                    if (i->get()==0){
                        m->remove(o);
                        b=true;
                    }
                }
            }
            return b;
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

        void JThread::takeOwner(){
            QObjectHolder::getQObjectHolder()->takeOwner(getQObject());
        }

        void JThread::releaseOwner(){
            QObjectHolder::getQObjectHolder()->releaseOwner(getQObject());
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
            QObjectHolder::getQObjectHolder()->deleteObject(getQObject());
            if (deletable){
                delete thread;
            }
        }
    }
}
