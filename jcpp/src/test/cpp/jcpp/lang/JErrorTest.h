#ifndef JERRORTEST_H
#define JERRORTEST_H

#include "JThrowableTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JErrorTest : public JThrowableTest{
        public:
            JErrorTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JErrorTest();
        };
    }
}


#endif // JERRORTEST_H
