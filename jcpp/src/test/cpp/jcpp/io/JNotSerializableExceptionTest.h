#ifndef JNOTSERIALIZABLEEXCEPTIONTEST_H
#define JNOTSERIALIZABLEEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JNotSerializableException.h"

namespace jcpp{
    namespace io{
        class JNotSerializableExceptionTest : public JObjectStreamExceptionTest{
        public:
            JNotSerializableExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JNotSerializableExceptionTest();
        };
    }
}

#endif // JNOTSERIALIZABLEEXCEPTIONTEST_H
