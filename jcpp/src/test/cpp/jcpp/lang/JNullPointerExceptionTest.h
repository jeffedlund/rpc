#ifndef JNULLPOINTEREXCEPTIONTEST_H
#define JNULLPOINTEREXCEPTIONTEST_H

#include "JRuntimeExceptionTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JNullPointerExceptionTest : public JRuntimeExceptionTest{
        public:
            JNullPointerExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JNullPointerExceptionTest();
        };
    }
}

#endif // JNULLPOINTEREXCEPTIONTEST_H
