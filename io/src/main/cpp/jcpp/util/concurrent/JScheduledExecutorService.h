#ifndef JSCHEDULEDEXECUTORSERVICE_H
#define JSCHEDULEDEXECUTORSERVICE_H

#include "JInterface.h"
#include "JClass.h"
#include "JExecutor.h"
#include "JFuture.h"
#include "JCallable.h"
#include "JExecutorService.h"
#include "JScheduledFuture.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledExecutorService : public JExecutorService{//TODO pas top
            protected:

            public:
                static JClass* getClazz();
                virtual JScheduledFuture* schedule(JCallable* callable, jlong delay)=0;
                virtual JScheduledFuture* schedule(JRunnable* command, jlong delay)=0;
                virtual JScheduledFuture* scheduleAtFixedRate(JRunnable* command, jlong initialDelay, jlong period)=0;
                virtual JScheduledFuture* scheduleWithFixedDelay(JRunnable* command, jlong initialDelay, jlong delay)=0;
            };
        }
    }
}


#endif // JSCHEDULEDEXECUTORSERVICE_H
