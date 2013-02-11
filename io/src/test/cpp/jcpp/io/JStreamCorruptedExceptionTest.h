#ifndef JSTREAMCORRUPTEDEXCEPTIONTEST_H
#define JSTREAMCORRUPTEDEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JStreamCorruptedException.h"

namespace jcpp{
    namespace io{
        class JStreamCorruptedExceptionTest : public JObjectStreamExceptionTest{
        public:
            JStreamCorruptedExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JSTREAMCORRUPTEDEXCEPTIONTEST_H
