#ifndef JNOTACTIVEEXCEPTIONTEST_H
#define JNOTACTIVEEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JNotActiveException.h"

namespace jcpp{
    namespace io{
        class JNotActiveExceptionTest : public JObjectStreamExceptionTest{
        public:
            JNotActiveExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JNotActiveExceptionTest();
        };
    }
}

#endif // JNOTACTIVEEXCEPTIONTEST_H
