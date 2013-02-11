#ifndef JCLASSCASTEXCEPTIONTEST_H
#define JCLASSCASTEXCEPTIONTEST_H

#include "JRuntimeExceptionTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JClassCastExceptionTest : public JRuntimeExceptionTest{
        public:
            JClassCastExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JCLASSCASTEXCEPTIONTEST_H
