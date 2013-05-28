#ifndef JOBJECT_H
#define JOBJECT_H

#include <QMutex>
#include <QWaitCondition>
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include <QThreadStorage>
#include "gc_cpp.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;
        class JString;

        class JCPP_LIBRARY_EXPORT JObject : public gc_cleanup{
            private:
                QMutex* mutex;
                QWaitCondition* waitCondition;

            protected:
                JClass* _class;
                JObject(JClass* _class);
                JObject(jbool root);

            public:
                struct POINTER_COMPARATOR{//TODO CRITICAL POSSIBLE BUG if 2 objects have the same hashcode in hashmap?
                    jbool operator()(JObject* e1, JObject* e2){
                        return (e1==NULL ? (e2==NULL ? true : 0<e2->hashCode()): e1->hashCode()<e2->hashCode());
                    }
                };

                struct POINTER_ID_COMPARATOR{
                    jbool operator()(JObject* e1, JObject* e2){
                        return (e1==NULL ? (e2==NULL ? true : 0<(jint)e2): (jint)e1<(jint)e2);
                    }
                };

                JObject();
                static JClass* getClazz();
                virtual JClass* getClass();
                virtual jbool operator==(JObject& other);
                virtual jbool operator!=(JObject& other);
                virtual jbool isInstanceOf(JClass* c);
                void lock();
                void unlock();
                void wait();
                void wait(jlong);
                void notify();
                void notifyAll();
                virtual jbool equals(JObject* o);
                virtual jint hashCode();
                virtual JString toString();
                virtual JObject* clone();
                virtual ~JObject();
        };

        JCPP_LIBRARY_EXPORT ostream& operator<<(ostream& os,jcpp::lang::JObject* o);
    }
}


#endif // JOBJECT_H
