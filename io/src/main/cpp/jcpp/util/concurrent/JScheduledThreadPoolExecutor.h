#ifndef JSCHEDULEDTHREADPOOLEXECUTOR_H
#define JSCHEDULEDTHREADPOOLEXECUTOR_H

#include "JInterface.h"
#include "JClass.h"
#include "JExecutor.h"
#include "JFuture.h"
#include "JCallable.h"
#include "JRunnable.h"
#include "JExecutorService.h"
#include "JScheduledExecutorService.h"
#include "JThreadPoolExecutor.h"
#include <QThreadPool>
#include "JTimer.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledThreadPoolExecutor : public JThreadPoolExecutor, public JScheduledExecutorService{
            protected:
                JTimer* timer;

            public:
                JScheduledThreadPoolExecutor();
                JScheduledThreadPoolExecutor(int maxPoolSize,int expiryTimeout);
                static JClass* getClazz();
                virtual void execute(JRunnable *command);
                virtual bool isShutdown();
                virtual void shutdown();
                virtual JFuture* submit(JRunnable* task);
                virtual JFuture* submit(JRunnable* task, JObject* result);
                virtual JFuture* submit(JCallable* task);
                virtual JScheduledFuture* schedule(JCallable* callable, jlong delay);
                virtual JScheduledFuture* schedule(JRunnable* command, jlong delay);
                virtual JScheduledFuture* schedule(JRunnable* command, jlong initialDelay, jlong period);
                virtual JScheduledFuture* schedule(JCallable* callable, jlong initialDelay, jlong period);
                ~JScheduledThreadPoolExecutor();
            };
        }
    }
}

#endif // JSCHEDULEDTHREADPOOLEXECUTOR_H