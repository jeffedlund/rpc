#ifndef JOBJECT_H
#define JOBJECT_H

#include <QMutex>
#include <QWaitCondition>
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;

        class JCPP_LIBRARY_EXPORT JObject{
            private:
                QMutex* mutex;
                QWaitCondition* waitCondition;

            protected:

                JClass* _class;
                JObject(JClass* _class);
                JObject(bool root);

            public:
                JObject();

                static JClass* getClazz();

                JClass* getClass();

                virtual bool operator==(JObject &other);//TODO implement other operators like !=

                virtual string toString();

                void lock();

                void unlock();

                void wait();

                void wait(jlong);

                void notify();

                void notifyAll();

                virtual JObject* clone();

                virtual ~JObject();
        };

        JCPP_LIBRARY_EXPORT ostream& operator<<(ostream& os,jcpp::lang::JObject* o);
    }
}


#endif // JOBJECT_H
