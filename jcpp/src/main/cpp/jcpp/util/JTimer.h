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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JTimerTask;
        class JCPP_LIBRARY_EXPORT JTimer : public JObject, public JRunnable{
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
                jbool setNextTime();
                void run();
            };

            jbool cancelled;
            QMutex* mutex;
            QWaitCondition* waitCondition;
            JThread* thread;
            vector<TimerItem*>* timerItems;
            virtual void run();
            void cancel(JTimerTask* task);
            friend class JTimerTask;

        public:
            JTimer();
            static JClass* getClazz();
            void cancel();
            jbool isCancelled();
            void schedule(JTimerTask* task, jlong delay);
            void schedule(JTimerTask* task, jlong delay, jlong period);
            virtual ~JTimer();
        };
    }
}

#endif // JTIMER_H
