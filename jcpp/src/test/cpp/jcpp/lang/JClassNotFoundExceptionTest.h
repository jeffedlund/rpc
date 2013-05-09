#ifndef JCLASSNOTFOUNDEXCEPTIONTEST_H
#define JCLASSNOTFOUNDEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JClassNotFoundExceptionTest : public JExceptionTest{
        public:
            JClassNotFoundExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JClassNotFoundExceptionTest();
        };
    }
}

#endif // JCLASSNOTFOUNDEXCEPTIONTEST_H
