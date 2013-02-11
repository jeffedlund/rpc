#ifndef JNOSUCHMETHODEXCEPTIONTEST_H
#define JNOSUCHMETHODEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JNoSuchMethodException.h"

namespace jcpp{
    namespace lang{
        class JNoSuchMethodExceptionTest : public JExceptionTest{
        public:
            JNoSuchMethodExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}


#endif // JNOSUCHMETHODEXCEPTIONTEST_H
