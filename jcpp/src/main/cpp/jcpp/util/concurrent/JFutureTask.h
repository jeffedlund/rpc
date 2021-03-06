#ifndef JFUTURETASK_H
#define JFUTURETASK_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnableFuture.h"
#include "JThrowable.h"
#include "JCallable.h"
#include "JRunnable.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JFutureTask : public JRunnableFuture, public JObject{
            protected:
                jbool bCancel;
                jbool bDone;
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
                jbool cancel();
                jbool isCancelled();
                jbool isDone();
                JObject* get();
                virtual ~JFutureTask();
            };
        }
    }
}

#endif // JFUTURETASK_H
