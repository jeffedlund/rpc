#ifndef JIOEXCEPTIONTEST_H
#define JIOEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JIOExceptionTest : public JExceptionTest{
        public:
            JIOExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JIOExceptionTest();
        };
    }
}

#endif // JIOEXCEPTIONTEST_H
