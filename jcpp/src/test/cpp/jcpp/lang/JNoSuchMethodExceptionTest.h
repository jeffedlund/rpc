#ifndef JNOSUCHMETHODEXCEPTIONTEST_H
#define JNOSUCHMETHODEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JNoSuchMethodException.h"

namespace jcpp{
    namespace lang{
        class JNoSuchMethodExceptionTest : public JExceptionTest{
        public:
            JNoSuchMethodExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JNoSuchMethodExceptionTest();
        };
    }
}


#endif // JNOSUCHMETHODEXCEPTIONTEST_H
