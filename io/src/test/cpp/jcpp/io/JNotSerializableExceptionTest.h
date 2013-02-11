#ifndef JNOTSERIALIZABLEEXCEPTIONTEST_H
#define JNOTSERIALIZABLEEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JNotSerializableException.h"

namespace jcpp{
    namespace io{
        class JNotSerializableExceptionTest : public JObjectStreamExceptionTest{
        public:
            JNotSerializableExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JNOTSERIALIZABLEEXCEPTIONTEST_H
