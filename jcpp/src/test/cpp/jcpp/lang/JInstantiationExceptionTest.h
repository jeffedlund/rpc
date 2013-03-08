#ifndef JINSTANTIATIONEXCEPTIONTEST_H
#define JINSTANTIATIONEXCEPTIONTEST_H

#include "JInstantiationExceptionTest.h"
#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        class JInstantiationExceptionTest : public JRuntimeExceptionTest{
        public:
            JInstantiationExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JInstantiationExceptionTest();
        };
    }
}

#endif // JINSTANTIATIONEXCEPTIONTEST_H
