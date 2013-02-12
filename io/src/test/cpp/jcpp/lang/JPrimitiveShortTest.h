#ifndef JPRIMITIVESHORTTEST_H
#define JPRIMITIVESHORTTEST_H

#include "JPrimitiveShort.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveShortTest : public JTest{
        public:
            JPrimitiveShortTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JPRIMITIVESHORTTEST_H
