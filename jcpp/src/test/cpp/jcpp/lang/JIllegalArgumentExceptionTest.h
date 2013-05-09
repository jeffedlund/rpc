#ifndef JILLEGALARGUMENTEXCEPTIONTEST_H
#define JILLEGALARGUMENTEXCEPTIONTEST_H

#include "JIllegalArgumentExceptionTest.h"
#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        class JIllegalArgumentExceptionTest : public JRuntimeExceptionTest{
        public:
            JIllegalArgumentExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JIllegalArgumentExceptionTest();
        };
    }
}

#endif // JILLEGALARGUMENTEXCEPTIONTEST_H
