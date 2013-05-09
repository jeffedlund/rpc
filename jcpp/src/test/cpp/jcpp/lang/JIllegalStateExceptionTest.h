#ifndef JILLEGALSTATEEXCEPTIONTEST_H
#define JILLEGALSTATEEXCEPTIONTEST_H

#include "JIllegalStateExceptionTest.h"
#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        class JIllegalStateExceptionTest : public JRuntimeExceptionTest{
        public:
            JIllegalStateExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JIllegalStateExceptionTest();
        };
    }
}

#endif // JILLEGALSTATEEXCEPTIONTEST_H
