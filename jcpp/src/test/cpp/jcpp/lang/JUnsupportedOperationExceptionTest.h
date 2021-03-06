#ifndef JUNSUPPORTEDOPERATIONEXCEPTIONTEST_H
#define JUNSUPPORTEDOPERATIONEXCEPTIONTEST_H

#include "JRuntimeExceptionTest.h"
#include "JUnsupportedOperationException.h"

namespace jcpp{
    namespace lang{
        class JUnsupportedOperationExceptionTest : public JRuntimeExceptionTest{
        public:
            JUnsupportedOperationExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JUnsupportedOperationExceptionTest();
        };
    }
}

#endif // JUNSUPPORTEDOPERATIONEXCEPTIONTEST_H
