#ifndef JINTEGERTEST_H
#define JINTEGERTEST_H

#include "JInteger.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JIntegerTest : public JTest{
        public:
            JIntegerTest();

            string getFileName();

            JObject* testReflect();

            virtual ~JIntegerTest();
        };
    }
}

#endif // JINTEGERTEST_H
