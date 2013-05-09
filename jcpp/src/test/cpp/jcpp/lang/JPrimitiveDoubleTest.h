#ifndef JPRIMITIVEDOUBLETEST_H
#define JPRIMITIVEDOUBLETEST_H

#include "JPrimitiveDouble.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveDoubleTest : public JTest{
        public:
            JPrimitiveDoubleTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JPrimitiveDoubleTest();
        };
    }
}

#endif // JPRIMITIVEDOUBLETEST_H
