#ifndef JTHREAD_H
#define JTHREAD_H

#include "JObject.h"
#include "JRunnable.h"
#include <QThread>
#include "QObjectAware.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JThread : public JObject, public JRunnable, public QObjectAware{
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

            QThread* thread;
            bool deletable;
            JRunnable* runnable;
            JThread(QThread* thread);

        public:
            JThread();
            JThread(JRunnable* runnable);
            static JClass* getClazz();
            static JThread* currentThread();
            static void sleep(jlong s);
            virtual QObject* getQObject();
            void move(QObjectAware* objectAware);//TODO really not great ...
            virtual void run();
            void start();
            string toString();
            ~JThread();
        };
    }
}

#endif // JTHREAD_H