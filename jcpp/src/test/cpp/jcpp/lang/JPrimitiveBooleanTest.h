#ifndef JPRIMITIVEBOOLEANTEST_H
#define JPRIMITIVEBOOLEANTEST_H

#include "JPrimitiveBoolean.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveBooleanTest : public JTest{
        public:
            JPrimitiveBooleanTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JPrimitiveBooleanTest();
        };
    }
}

#endif // JPRIMITIVEBOOLEANTEST_H
