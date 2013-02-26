#ifndef JERRORTEST_H
#define JERRORTEST_H

#include "JThrowableTest.h"
#include "JError.h"

namespace jcpp{
    namespace lang{
        class JErrorTest : public JThrowableTest{
        public:
            JErrorTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JErrorTest();
        };
    }
}


#endif // JERRORTEST_H
