#ifndef JSCHEDULEDEXECUTORSERVICETEST_H
#define JSCHEDULEDEXECUTORSERVICETEST_H

#include "JScheduledExecutorService.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledExecutorServiceTest : public JTest{
            public:
                JScheduledExecutorServiceTest();

                virtual void test();

                virtual ~JScheduledExecutorServiceTest();
            };
        }
    }
}

#endif // JSCHEDULEDEXECUTORSERVICETEST_H
