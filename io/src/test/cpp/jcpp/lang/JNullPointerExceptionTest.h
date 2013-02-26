#ifndef JNULLPOINTEREXCEPTIONTEST_H
#define JNULLPOINTEREXCEPTIONTEST_H

#include "JRuntimeExceptionTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JNullPointerExceptionTest : public JRuntimeExceptionTest{
        public:
            JNullPointerExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JNullPointerExceptionTest();
        };
    }
}

#endif // JNULLPOINTEREXCEPTIONTEST_H
