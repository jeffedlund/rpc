#ifndef JCLASSNOTFOUNDEXCEPTIONTEST_H
#define JCLASSNOTFOUNDEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JClassNotFoundExceptionTest : public JExceptionTest{
        public:
            JClassNotFoundExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JCLASSNOTFOUNDEXCEPTIONTEST_H
