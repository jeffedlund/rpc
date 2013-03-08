#ifndef JBITSTEST_H
#define JBITSTEST_H

#include "JBits.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JBitsTest : public JTest{
        public:
            JBitsTest();

            virtual void test();

            virtual ~JBitsTest();
        };
    }
}

#endif // JBITSTEST_H
