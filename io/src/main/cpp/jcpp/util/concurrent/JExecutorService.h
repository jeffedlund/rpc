#ifndef JEXECUTORSERVICE_H
#define JEXECUTORSERVICE_H

#include "JInterface.h"
#include "JClass.h"
#include "JExecutor.h"
#include "JFuture.h"
#include "JCallable.h"
#include "JRunnable.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JExecutorService : public JExecutor{
            protected:

            public:
                static JClass* getClazz();
                virtual void shutdown()=0;
                virtual bool isShutdown()=0;
                virtual JFuture* submit(JCallable* task)=0;
                virtual JFuture* submit(JRunnable* task,JObject* result)=0;
                virtual JFuture* submit(JRunnable* task)=0;
            };
        }
    }
}

#endif // JEXECUTORSERVICE_H
