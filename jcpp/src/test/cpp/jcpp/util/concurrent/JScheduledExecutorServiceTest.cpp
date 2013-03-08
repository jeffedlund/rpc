#include "JScheduledExecutorServiceTest.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            JScheduledExecutorServiceTest::JScheduledExecutorServiceTest():JTest(){
            }

            class MyCallable : public JCallable{
            public:
                MyCallable():JCallable(){
                }

                JObject* call(){
                    cout<<"my run "<<JSystem::currentTimeMillis()<<"\r\n";
                    cout.flush();
                    return new JString("result");
                }
                ~MyCallable(){
                }
            };

            void JScheduledExecutorServiceTest::test(){
                JScheduledExecutorService* es=new JScheduledThreadPoolExecutor();
                JScheduledFuture* future=es->schedule(new MyCallable(),5000, 3000);
                JThread::sleep(20);
                future->cancel();
                cout<<"Canceled!\r\n";
                cout.flush();
                JThread::sleep(10000);
            }

            JScheduledExecutorServiceTest::~JScheduledExecutorServiceTest(){
            }
        }
    }
}



