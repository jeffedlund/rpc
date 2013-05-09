#ifndef JINVALIDCLASSEXCEPTIONTEST_H
#define JINVALIDCLASSEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JInvalidClassException.h"

namespace jcpp{
    namespace io{
        class JInvalidClassExceptionTest : public JObjectStreamExceptionTest{
        public:
            JInvalidClassExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JInvalidClassExceptionTest();
        };
    }
}

#endif // JINVALIDEXCEPTIONTEST_H
