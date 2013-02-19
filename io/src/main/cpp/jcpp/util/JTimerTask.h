#ifndef JTIMERTASK_H
#define JTIMERTASK_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnable.h"
#include "JTimer.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JTimer;
        class JTimerTask : public JRunnable, public JObject{
        protected:
            bool bCancelled;
            JTimer* timer;
            JTimerTask(JClass* _class);

        public:
            static JClass* getClazz();

            void setTimer(JTimer* timer);
            void cancel();
            bool isCancelled();
            virtual void run()=0;
        };
    }
}

#endif // JTIMERTASK_H