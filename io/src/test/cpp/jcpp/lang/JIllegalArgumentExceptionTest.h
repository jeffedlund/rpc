#ifndef JILLEGALARGUMENTEXCEPTIONTEST_H
#define JILLEGALARGUMENTEXCEPTIONTEST_H

#include "JIllegalArgumentExceptionTest.h"
#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        class JIllegalArgumentExceptionTest : public JRuntimeExceptionTest{
        public:
            JIllegalArgumentExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JILLEGALARGUMENTEXCEPTIONTEST_H
