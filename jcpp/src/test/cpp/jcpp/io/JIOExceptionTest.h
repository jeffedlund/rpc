#ifndef JIOEXCEPTIONTEST_H
#define JIOEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JIOExceptionTest : public JExceptionTest{
        public:
            JIOExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JIOExceptionTest();
        };
    }
}

#endif // JIOEXCEPTIONTEST_H
