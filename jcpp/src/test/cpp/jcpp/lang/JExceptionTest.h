#ifndef JEXCEPTIONTEST_H
#define JEXCEPTIONTEST_H

#include "JThrowableTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JExceptionTest : public JThrowableTest{
        public:
            JExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JExceptionTest();
        };
    }
}


#endif // JEXCEPTIONTEST_H
