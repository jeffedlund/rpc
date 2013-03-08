#ifndef JEXCEPTIONTEST_H
#define JEXCEPTIONTEST_H

#include "JThrowableTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JExceptionTest : public JThrowableTest{
        public:
            JExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JExceptionTest();
        };
    }
}


#endif // JEXCEPTIONTEST_H
