#include "JTimer.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>
#include "JSystem.h"
using namespace std;

namespace jcpp{
    namespace util{
        class JTimerClass : public JClass{

        public:
          JTimerClass(){
              this->canonicalName="java.util.Task";
              this->name="java.util.Task";
              this->simpleName="Task";
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }

          JObject* newInstance(){
              return new JTimer();
          }
        };

        static JClass* clazz;

        JClass* JTimer::getClazz(){
            if (clazz==NULL){
                clazz=new JTimerClass();
            }
            return clazz;
        }

        JTimer::TimerItem::TimerItem(JTimerTask* task,jlong delay,jlong period){
            this->task=task;
            this->delay=delay;
            this->period=period;
            this->nextTime=JSystem::currentTimeMillis()+delay;
        }

        JTimerTask* JTimer::TimerItem::getTask(){
            return task;
        }

        jlong JTimer::TimerItem::getNextTime(){
            return nextTime;
        }

        bool JTimer::TimerItem::setNextTime(){
            if (period>0){
                this->nextTime=nextTime+period;
                return true;
            }
            return false;
        }

        void JTimer::TimerItem::run(){
            if (!task->isCancelled()){
                task->run();
            }
        }

        JTimer::JTimer():JObject(getClazz()){
            this->cancelled=false;
            this->mutex=new QMutex();
            this->waitCondition=new QWaitCondition();
            this->timerItems=new vector<TimerItem*>();
            this->thread=new JThread(this);
            thread->start();
        }

        void JTimer::run(){
            vector<TimerItem*>* todos=new vector<TimerItem*>();
            while (!isCancelled()){
                mutex->lock();
                if (cancelled){
                    mutex->unlock();
                    break;
                }
                jlong now=JSystem::currentTimeMillis();
                vector<TimerItem*>::iterator it;
                for (it=timerItems->begin();it!=timerItems->end();){
                    TimerItem* item=(*it);
                    if (item->getNextTime()<=now){
                        todos->push_back(item);
                        if (item->setNextTime()){
                            it++;
                        }else{
                            it=timerItems->erase(it);
                        }
                    }else{
                        it++;
                    }
                }
                mutex->unlock();
                for (unsigned int i=0;i<todos->size();i++){
                    TimerItem* item=todos->at(i);
                    item->run();
                }
                todos->clear();

                mutex->lock();
                if (cancelled){
                    mutex->unlock();
                    break;
                }
                jlong lowestTime=-1;
                now=JSystem::currentTimeMillis();
                for (it=timerItems->begin();it!=timerItems->end();it++){
                    TimerItem* item=(*it);
                    lowestTime=(lowestTime==-1 || item->getNextTime()<lowestTime ? item->getNextTime() : lowestTime);
                }
                jlong time=lowestTime-now;
                if (lowestTime==-1){
                    waitCondition->wait(mutex);
                }else{
                    if (time>0){
                        waitCondition->wait(mutex,time);
                    }
                }
                mutex->unlock();
            }
            delete todos;
        }

        void JTimer::cancel(){
            mutex->lock();
            this->cancelled=true;
            waitCondition->wakeAll();
            mutex->unlock();
        }

        bool JTimer::isCancelled(){
            bool b;
            mutex->lock();
            b=this->cancelled;
            mutex->unlock();
            return b;
        }

        void JTimer::schedule(JTimerTask* task, jlong delay){
            task->setTimer(this);
            mutex->lock();
            timerItems->push_back(new TimerItem(task, delay,0));
            waitCondition->wakeAll();
            mutex->unlock();
        }

        void JTimer::schedule(JTimerTask* task, jlong delay, jlong period){
            task->setTimer(this);
            mutex->lock();
            timerItems->push_back(new TimerItem(task, delay,period));
            waitCondition->wakeAll();
            mutex->unlock();
        }

        void JTimer::cancel(JTimerTask* task){
            mutex->lock();
            vector<TimerItem*>::iterator it;
            for (it=timerItems->begin();it!=timerItems->end();){
                TimerItem* item=(*it);
                if (item->getTask()==task){
                    it=timerItems->erase(it);
                }else{
                    it++;
                }
            }
            waitCondition->wakeAll();
            mutex->unlock();
        }

        JTimer::~JTimer(){
            delete thread;
            delete mutex;
            delete waitCondition;
        }
    }
}
