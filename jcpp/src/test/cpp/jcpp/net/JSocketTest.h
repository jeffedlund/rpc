#ifndef JSOCKETTEST_H
#define JSOCKETTEST_H

#include "JSocket.h"
#include "JTest.h"

namespace jcpp{
    namespace net{
        class JSocketTest : public JTest{
        public:
            JSocketTest();

            virtual void test();

            virtual ~JSocketTest();
        };
    }
}

#endif // JSOCKETTEST_H
