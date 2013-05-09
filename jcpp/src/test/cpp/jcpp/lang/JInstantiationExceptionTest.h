#ifndef JINSTANTIATIONEXCEPTIONTEST_H
#define JINSTANTIATIONEXCEPTIONTEST_H

#include "JInstantiationExceptionTest.h"
#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        class JInstantiationExceptionTest : public JRuntimeExceptionTest{
        public:
            JInstantiationExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JInstantiationExceptionTest();
        };
    }
}

#endif // JINSTANTIATIONEXCEPTIONTEST_H
