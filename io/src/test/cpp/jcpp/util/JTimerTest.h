#ifndef JTIMERTEST_H
#define JTIMERTEST_H

#include "JTimer.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JTimerTest : public JTest{
        public:
            JTimerTest();

            virtual void test();

            virtual ~JTimerTest();
        };
    }
}

#endif // JTIMERTEST_H
