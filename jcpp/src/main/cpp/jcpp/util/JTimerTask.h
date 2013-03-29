#ifndef JTIMERTASK_H
#define JTIMERTASK_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnable.h"
#include "JTimer.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JTimer;
        class JCPP_LIBRARY_EXPORT JTimerTask : public JRunnable, public JObject{
        protected:
            bool bCancelled;
            JTimer* timer;
            JTimerTask(JClass* _class);
            friend class JTimer;

        public:
            static JClass* getClazz();
            virtual bool cancel();
            bool isCancelled();
            virtual void run()=0;
            virtual ~JTimerTask()=0;
        };
    }
}

#endif // JTIMERTASK_H
