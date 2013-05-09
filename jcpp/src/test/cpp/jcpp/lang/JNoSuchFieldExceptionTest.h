#ifndef JNOSUCHFIELDEXCEPTIONTEST_H
#define JNOSUCHFIELDEXCEPTIONTEST_H

#include "JExceptionTest.h"
#include "JNoSuchFieldException.h"

namespace jcpp{
    namespace lang{
        class JNoSuchFieldExceptionTest : public JExceptionTest{
        public:
            JNoSuchFieldExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JNoSuchFieldExceptionTest();
        };
    }
}

#endif // JNOSUCHFIELDEXCEPTIONTEST_H
