#ifndef JPRIMITIVEFLOATTEST_H
#define JPRIMITIVEFLOATTEST_H

#include "JPrimitiveFloat.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveFloatTest : public JTest{
        public:
            JPrimitiveFloatTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}


#endif // JPRIMITIVEFLOATTEST_H
