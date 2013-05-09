#ifndef JPRIMITIVEINTTEST_H
#define JPRIMITIVEINTTEST_H

#include "JPrimitiveInt.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveIntTest : public JTest{
        public:
            JPrimitiveIntTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JPrimitiveIntTest();
        };
    }
}

#endif // JPRIMITIVEINTTEST_H
