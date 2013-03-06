#ifndef JTIMER_H
#define JTIMER_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnable.h"
#include <QMutex>
#include <QWaitCondition>
#include "JTimerTask.h"
#include "JThread.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JTimerTask;
        class JTimer : public JObject, public JRunnable{
        protected:
            class TimerItem{
            protected:
                JTimerTask* task;
                jlong delay;
                jlong period;
                jlong nextTime;
            public:
                TimerItem(JTimerTask* task,jlong delay,jlong period);

                JTimerTask* getTask();
                jlong getNextTime();
                bool setNextTime();
                void run();
            };

            bool cancelled;
            QMutex* mutex;
            QWaitCondition* waitCondition;
            JThread* thread;
            vector<TimerItem*>* timerItems;
            virtual void run();

        public:
            JTimer();
            static JClass* getClazz();
            void cancel();
            bool isCancelled();
            void schedule(JTimerTask* task, jlong delay);
            void schedule(JTimerTask* task, jlong delay, jlong period);
            void cancel(JTimerTask* task);
            virtual ~JTimer();
        };
    }
}

#endif // JTIMER_H
