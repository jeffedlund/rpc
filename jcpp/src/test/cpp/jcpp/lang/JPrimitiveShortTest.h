#ifndef JPRIMITIVESHORTTEST_H
#define JPRIMITIVESHORTTEST_H

#include "JPrimitiveShort.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveShortTest : public JTest{
        public:
            JPrimitiveShortTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JPrimitiveShortTest();
        };
    }
}

#endif // JPRIMITIVESHORTTEST_H
