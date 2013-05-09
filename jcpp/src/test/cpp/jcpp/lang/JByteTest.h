#ifndef JBYTETEST_H
#define JBYTETEST_H

#include "JByte.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JByteTest : public JTest{
        public:
            JByteTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JByteTest();
        };
    }
}

#endif // JBYTETEST_H
