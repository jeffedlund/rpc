#ifndef JENUMTEST_H
#define JENUMTEST_H

#include "JEnum.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JEnumTest : public JTest{
        public:
            JEnumTest();

            string getFileName();

            JObject* testReflect();

            virtual ~JEnumTest();
        };
    }
}
#endif // JENUMTEST_H
