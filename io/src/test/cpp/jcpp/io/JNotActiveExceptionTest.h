#ifndef JNOTACTIVEEXCEPTIONTEST_H
#define JNOTACTIVEEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JNotActiveException.h"

namespace jcpp{
    namespace io{
        class JNotActiveExceptionTest : public JObjectStreamExceptionTest{
        public:
            JNotActiveExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JNOTACTIVEEXCEPTIONTEST_H
