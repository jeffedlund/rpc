#ifndef JSCHEDULEDFUTURETASK_H
#define JSCHEDULEDFUTURETASK_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnableFuture.h"
#include "JThrowable.h"
#include "JCallable.h"
#include "JRunnableScheduledFuture.h"
#include "JFutureTask.h"
#include "JTimerTask.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledFutureTask : public JRunnableScheduledFuture, public JTimerTask{
            protected:
                jlong initialDelay;
                jlong period;
                bool bCancel;
                bool bDone;
                JCallable* callable;
                JRunnable* runnable;
                JObject* result;
                JScheduledFutureTask(JClass* _class);

            public:
                JScheduledFutureTask(JCallable* c,long initialDelay, jlong period);
                JScheduledFutureTask(JRunnable* r,JObject* result,long initialDelay, jlong period);
                static JClass* getClazz();

                virtual void run();
                bool cancel();
                bool isCancelled();
                bool isDone();
                JObject* get();
                bool isPeriodic();
                jlong getDelay();
                long getPeriod();
            };
        }
    }
}

#endif // JSCHEDULEDFUTURETASK_H
