#ifndef JPRIMITIVEBYTETEST_H
#define JPRIMITIVEBYTETEST_H

#include "JPrimitiveByte.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveByteTest : public JTest{
        public:
            JPrimitiveByteTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JPRIMITIVEBYTETEST_H
