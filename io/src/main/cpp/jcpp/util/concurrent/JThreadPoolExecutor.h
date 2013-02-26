#ifndef JTHREADPOOLEXECUTOR_H
#define JTHREADPOOLEXECUTOR_H

#include "JInterface.h"
#include "JClass.h"
#include "JExecutor.h"
#include "JFuture.h"
#include "JCallable.h"
#include "JRunnable.h"
#include "JExecutorService.h"
#include "JAbstractExecutorService.h"
#include <QThreadPool>
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JThreadPoolExecutor : public JAbstractExecutorService{
            protected:
                bool bShutdown;
                QThreadPool* threadPool;
                JThreadPoolExecutor(int maxPoolSize,int expiryTimeout,JClass* _class);

            public:
                JThreadPoolExecutor();
                JThreadPoolExecutor(int maxPoolSize,int expiryTimeout);
                static JClass* getClazz();
                virtual void execute(JRunnable *command);
                virtual bool isShutdown();
                virtual void shutdown();
                virtual ~JThreadPoolExecutor();
            };
        }
    }
}

#endif // JTHREADPOOLEXECUTOR_H
