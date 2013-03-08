#include "JTimerTest.h"

namespace jcpp{
    namespace util{
        JTimerTest::JTimerTest():JTest(){
        }

        class MyTimerTask : public JTimerTask{
        public:
            MyTimerTask():JTimerTask(NULL){
            }

            void run(){
                cout<<"my run "<<JSystem::currentTimeMillis()<<"\r\n";
                cout.flush();
            }
        };

        void JTimerTest::test(){
            JTimer* timer=new JTimer();
            MyTimerTask* my=new MyTimerTask();
            timer->schedule(my,5000, 3000);
        }

        JTimerTest::~JTimerTest(){
        }
    }
}



