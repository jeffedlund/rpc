#ifndef JINDEXOUTOFBOUNDSEXCEPTIONTEST_H
#define JINDEXOUTOFBOUNDSEXCEPTIONTEST_H

#include "JIndexOutOfBoundsExceptionTest.h"
#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        class JIndexOutOfBoundsExceptionTest : public JRuntimeExceptionTest{
        public:
            JIndexOutOfBoundsExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JIndexOutOfBoundsExceptionTest();
        };
    }
}

#endif // JINDEXOUTOFBOUNDSEXCEPTIONTEST_H
