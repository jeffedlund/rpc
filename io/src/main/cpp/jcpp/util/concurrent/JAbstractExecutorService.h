#ifndef JABSTRACTEXECUTORSERVICE_H
#define JABSTRACTEXECUTORSERVICE_H

#include "JInterface.h"
#include "JClass.h"
#include "JExecutor.h"
#include "JFuture.h"
#include "JCallable.h"
#include "JRunnable.h"
#include "JRunnableFuture.h"
#include "JExecutorService.h"
#include "JFutureTask.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JAbstractExecutorService : public JExecutorService, public JObject{
            protected:
                JAbstractExecutorService(JClass* _class);
                JRunnableFuture* newTaskFor(JRunnable* runnable, JObject* result);
                JRunnableFuture* newTaskFor(JCallable* callable);

            public:
                static JClass* getClazz();
                virtual JFuture* submit(JRunnable* task);
                virtual JFuture* submit(JRunnable* task, JObject* result);
                virtual JFuture* submit(JCallable* task);
            };
        }
    }
}

#endif // JABSTRACTEXECUTORSERVICE_H
