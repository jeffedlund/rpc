#ifndef JTRANSPORTTEST_H
#define JTRANSPORTTEST_H

#include "JTransport.h"
#include "JTest.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JTransportTest : public JTest{
                    public:
                        JTransportTest();

                        virtual void test();

                        virtual ~JTransportTest();
                    };
                }
            }
        }
    }
}

#endif // JTRANSPORTTEST_H
