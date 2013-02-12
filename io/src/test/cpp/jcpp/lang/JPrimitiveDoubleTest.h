#ifndef JPRIMITIVEDOUBLETEST_H
#define JPRIMITIVEDOUBLETEST_H

#include "JPrimitiveDouble.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveDoubleTest : public JTest{
        public:
            JPrimitiveDoubleTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JPRIMITIVEDOUBLETEST_H
