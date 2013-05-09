#ifndef JRUNTIMEEXCEPTIONTEST_H
#define JRUNTIMEEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JRuntimeExceptionTest : public JExceptionTest{
        public:
            JRuntimeExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JRuntimeExceptionTest();
        };
    }
}

#endif // JRUNTIMEEXCEPTION_H
