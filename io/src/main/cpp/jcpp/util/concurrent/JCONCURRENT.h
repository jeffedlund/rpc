#ifndef JCONCURRENT_H
#define JCONCURRENT_H

#include "JUTIL.h"
#include "JPackage.h"
#include "JAbstractExecutorService.h"
#include "JCallable.h"
#include "JDelayed.h"
#include "JExecutor.h"
#include "JExecutorService.h"
#include "JFuture.h"
#include "JFutureTask.h"
#include "JRunnableFuture.h"
#include "JRunnableScheduledFuture.h"
#include "JScheduledExecutorService.h"
#include "JScheduledFuture.h"
#include "JScheduledFutureTask.h"
#include "JScheduledThreadPoolExecutor.h"
#include "JThreadPoolExecutor.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCONCURRENT : public JPackage{
            protected:
                JCONCURRENT();

            public:
                JPackage* getSuperPackage();

                vector<JPackage*>* getPackages();

                static JCONCURRENT* getPackage();
            };
        }
    }
}

#endif // JCONCURRENT_H
