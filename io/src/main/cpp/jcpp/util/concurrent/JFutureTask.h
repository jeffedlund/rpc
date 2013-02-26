#ifndef JFUTURETASK_H
#define JFUTURETASK_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnableFuture.h"
#include "JThrowable.h"
#include "JCallable.h"
#include "JRunnable.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JFutureTask : public JRunnableFuture, public JObject{
            protected:
                bool bCancel;
                bool bDone;
                JCallable* callable;
                JRunnable* runnable;
                JObject* result;
                JFutureTask(JClass* _class);
                virtual void setResult(JObject* result);

            public:
                JFutureTask(JCallable* c);
                JFutureTask(JRunnable* r,JObject* result);
                static JClass* getClazz();

                void run();
                bool cancel();
                bool isCancelled();
                bool isDone();
                JObject* get();
                virtual ~JFutureTask();
            };
        }
    }
}

#endif // JFUTURETASK_H
