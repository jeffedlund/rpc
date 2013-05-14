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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JScheduledFutureTask : public JRunnableScheduledFuture, public JTimerTask{
            protected:
                jlong initialDelay;
                jlong period;
                jbool bDone;
                JCallable* callable;
                JRunnable* runnable;
                JObject* initialResult;
                JObject* result;
                JScheduledFutureTask(JClass* _class);
                virtual void setResult(JObject *result);

            public:
                JScheduledFutureTask(JCallable* c,jlong initialDelay, jlong period);
                JScheduledFutureTask(JRunnable* r,JObject* result,jlong initialDelay, jlong period);
                static JClass* getClazz();
                virtual void run();
                virtual jbool cancel();
                virtual jbool isCancelled();
                jbool isDone();
                JObject* get();
                jbool isPeriodic();
                jlong getDelay();
                jlong getPeriod();
                virtual ~JScheduledFutureTask();
            };
        }
    }
}

#endif // JSCHEDULEDFUTURETASK_H
