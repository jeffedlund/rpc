#ifndef JILLEGALSTATEEXCEPTIONTEST_H
#define JILLEGALSTATEEXCEPTIONTEST_H

#include "JIllegalStateExceptionTest.h"
#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        class JIllegalStateExceptionTest : public JRuntimeExceptionTest{
        public:
            JIllegalStateExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JILLEGALSTATEEXCEPTIONTEST_H
