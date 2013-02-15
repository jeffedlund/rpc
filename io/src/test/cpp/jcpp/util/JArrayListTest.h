#ifndef JARRAYLISTTEST_H
#define JARRAYLISTTEST_H

#include "JArrayList.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JArrayListTest : public JTest{
        public:
            JArrayListTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JARRAYLISTTEST_H
