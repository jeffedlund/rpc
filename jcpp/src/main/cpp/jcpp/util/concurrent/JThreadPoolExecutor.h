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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JThreadPoolExecutor : public JAbstractExecutorService{
            protected:
                jbool bShutdown;
                QThreadPool* threadPool;
                JThreadPoolExecutor(jint maxPoolSize,jint expiryTimeout,JClass* _class);

            public:
                JThreadPoolExecutor();
                JThreadPoolExecutor(jint maxPoolSize,jint expiryTimeout);
                static JClass* getClazz();
                virtual void execute(JRunnable *command);
                virtual jbool isShutdown();
                virtual void shutdown();
                virtual ~JThreadPoolExecutor();
            };
        }
    }
}

#endif // JTHREADPOOLEXECUTOR_H
