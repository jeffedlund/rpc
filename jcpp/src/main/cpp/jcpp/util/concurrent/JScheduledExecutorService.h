#ifndef JSCHEDULEDEXECUTORSERVICE_H
#define JSCHEDULEDEXECUTORSERVICE_H

#include "JInterface.h"
#include "JClass.h"
#include "JExecutor.h"
#include "JFuture.h"
#include "JCallable.h"
#include "JExecutorService.h"
#include "JScheduledFuture.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JScheduledExecutorService : public JExecutorService{
            public:
                static JClass* getClazz();
                virtual JScheduledFuture* schedule(JCallable* callable, jlong delay)=0;
                virtual JScheduledFuture* schedule(JRunnable* command, jlong delay)=0;
                virtual JScheduledFuture* schedule(JRunnable* command, jlong initialDelay, jlong period)=0;
                virtual JScheduledFuture* schedule(JCallable* callable, jlong initialDelay, jlong period)=0;
                virtual ~JScheduledExecutorService();
            };
        }
    }
}


#endif // JSCHEDULEDEXECUTORSERVICE_H
