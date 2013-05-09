#ifndef JSTRINGBUFFERTEST_H
#define JSTRINGBUFFERTEST_H


#include "JStringBuffer.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JStringBufferTest : public JTest{
        public:
            JStringBufferTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JStringBufferTest();
        };
    }
}

#endif // JSTRINGBUFFERTEST_H
