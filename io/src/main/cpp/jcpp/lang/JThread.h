#ifndef JTHREAD_H
#define JTHREAD_H

#include "JObject.h"
#include "JRunnable.h"
#include <QThread>
using namespace std;

namespace jcpp{
    namespace lang{
        class JThread : public JObject, public JRunnable{
        protected:
            class JQThread : public QThread{
                JRunnable* runnable;

            public:
                JQThread(JRunnable* runnable){
                    this->runnable=runnable;
                }
                void run(){
                    runnable->run();
                }
                static void extSleep(jlong s){
                    sleep(s);
                }
            };


            JRunnable* runnable;
            JThread(QThread* thread);

        public:
            QThread* thread;
            JThread();
            JThread(JRunnable* runnable);
            static JClass* getClazz();
            static JThread* currentThread();
            static void sleep(jlong s);
            virtual void run();
            void start();
            string toString();
            ~JThread();
        };
    }
}

#endif // JTHREAD_H
