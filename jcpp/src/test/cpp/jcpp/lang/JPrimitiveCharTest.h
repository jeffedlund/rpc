#ifndef JPRIMITIVECHARTEST_H
#define JPRIMITIVECHARTEST_H

#include "JPrimitiveChar.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveCharTest : public JTest{
        public:
            JPrimitiveCharTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JPrimitiveCharTest();
        };
    }
}

#endif // JPRIMITIVECHARTEST_H
