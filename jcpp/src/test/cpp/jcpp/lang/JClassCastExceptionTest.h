#ifndef JCLASSCASTEXCEPTIONTEST_H
#define JCLASSCASTEXCEPTIONTEST_H

#include "JRuntimeExceptionTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JClassCastExceptionTest : public JRuntimeExceptionTest{
        public:
            JClassCastExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JClassCastExceptionTest();
        };
    }
}

#endif // JCLASSCASTEXCEPTIONTEST_H
