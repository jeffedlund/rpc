#ifndef JHASHMAPTEST_H
#define JHASHMAPTEST_H

#include "JHashMap.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JHashMapTest : public JTest{
        public:
            JHashMapTest();

            string getFileName();

            JObject* testReflect();

            virtual ~JHashMapTest();
        };
    }
}
#endif // JHASHMAPTEST_H
