#include "JTimerTask.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JTimerTaskClass : public JClass{

        public:
          JTimerTaskClass(){
              this->canonicalName="java.util.TimerTask";
              this->name="java.util.TimerTask";
              this->simpleName="TimerTask";
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

        JClass* JTimerTask::getClazz(){
            if (clazz==NULL){
                clazz=new JTimerTaskClass();
            }
            return clazz;
        }

        JTimerTask::JTimerTask(JClass* _class):JObject(_class){
            this->bCancelled=false;
        }

        void JTimerTask::setTimer(JTimer* timer){
            this->timer=timer;
        }

        bool JTimerTask::cancel(){
            lock();
            this->bCancelled=true;
            unlock();
            if (timer!=NULL){
                timer->cancel(this);
            }
            return true;
        }

        bool JTimerTask::isCancelled(){
            bool b;
            lock();
            b=bCancelled;
            unlock();
            return b;
        }

        JTimerTask::~JTimerTask(){
        }
    }
}
