#ifndef JINVALIDCLASSEXCEPTIONTEST_H
#define JINVALIDCLASSEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JInvalidClassException.h"

namespace jcpp{
    namespace io{
        class JInvalidClassExceptionTest : public JObjectStreamExceptionTest{
        public:
            JInvalidClassExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JInvalidClassExceptionTest();
        };
    }
}

#endif // JINVALIDEXCEPTIONTEST_H
