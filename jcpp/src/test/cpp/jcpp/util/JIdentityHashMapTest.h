#ifndef JIDENTITYHASHMAPTEST_H
#define JIDENTITYHASHMAPTEST_H


#include "JIdentityHashMap.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JIdentityHashMapTest : public JTest{
        public:
            JIdentityHashMapTest();

            virtual bool applyEqual(){
                return false;
            }

            JString getFileName();

            JObject* testReflect();

            virtual ~JIdentityHashMapTest();
        };
    }
}
#endif // JIDENTITYHASHMAPTEST_H
