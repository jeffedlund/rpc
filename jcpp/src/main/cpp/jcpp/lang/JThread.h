#ifndef JTHREAD_H
#define JTHREAD_H

#include "JObject.h"
#include "JRunnable.h"
#include <QThread>
#include "QObjectAware.h"
#include "JCPP.h"
#include "JThreadLocal.h"
#include "JThrowable.h"
using namespace std;

//TODO implement more methods + getContextClassLoader
namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JThread : public JObject, public JRunnable, public QObjectAware{
        public:
            class JCPP_LIBRARY_EXPORT JUncaughtExceptionHandler : public JInterface{
            public:
                static JClass* getClazz();
                virtual void uncaughtException(JThread* t, JThrowable* e)=0;
                virtual ~JUncaughtExceptionHandler();
            };
            static JUncaughtExceptionHandler* getDefaultUncaughtExceptionHandler();
            static void setDefaultUncaughtExceptionHandler(JUncaughtExceptionHandler* eh);

        protected:
            class JQThread : public QThread{
                JRunnable* runnable;

            public:
                JQThread(JRunnable* runnable){
                    this->runnable=runnable;
                }
                void run(){
                    try{
                        runnable->run();
                    }catch(JThrowable* th){
                        th->printStackTrace(&cout);//TODO call JUncaughtExceptionHandler
                    }
                }
                static void extSleep(jlong s){
                    sleep(s);
                }
            };

            QThread* thread;
            bool deletable;
            JRunnable* runnable;
            JUncaughtExceptionHandler* ueh;
            JThread(QThread* thread);

            static jbool addObjectLocked(JObject* o);
            static jbool removeObjectLocked(JObject* o);
            friend class JObject;

        public:
            JThread();
            JThread(JRunnable* runnable);
            static JClass* getClazz();
            static JThread* currentThread();
            static void sleep(jlong s);
            virtual void takeOwner();
            virtual void releaseOwner();
            virtual QObject* getQObject();
            void move(QObjectAware* objectAware);
            JUncaughtExceptionHandler* getUncaughtExceptionHandler();
            void setUncaughtExceptionHandler(JUncaughtExceptionHandler* eh);
            virtual void run();
            void start();
            string toString();
            virtual ~JThread();
        };
    }
}

#endif // JTHREAD_H
