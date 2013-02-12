#ifndef JBYTETEST_H
#define JBYTETEST_H

#include "JByte.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JByteTest : public JTest{
        public:
            JByteTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JBYTETEST_H
