#ifndef JSERVERTEST_H
#define JSERVERTEST_H

#include "JServer.h"
#include "JTest.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JServerTest : public JTest{
                    public:
                        JServerTest();

                        virtual void test();

                        virtual ~JServerTest();
                    };
                }
            }
        }
    }
}

#endif // JSERVERTEST_H
