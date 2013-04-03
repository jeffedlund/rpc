#ifndef JPRIMITIVEARRAYTEST_H
#define JPRIMITIVEARRAYTEST_H


#include "JPrimitiveArray.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveArrayTest : public JTest{
        public:
            JPrimitiveArrayTest();

            string getFileName();

            JObject* testReflect();

            virtual ~JPrimitiveArrayTest();
        };
    }
}

#endif // JPRIMITIVEARRAYTEST_H
