#ifndef JOBJECT_H
#define JOBJECT_H

#include <QMutex>
#include <QWaitCondition>
#include <vector>
#include <map>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include <QThreadStorage>
#include <mutex>
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;
        class JString;

        class JCPP_LIBRARY_EXPORT JObject{
            private:
                QMutex* qmutex;
                QWaitCondition* waitCondition;
                recursive_mutex* memoryMutex;
                class JINT{
                private:
                    jint value;
                public:
                    JINT(jint v){
                        this->value=v;
                    }

                    jint getValue(){
                        return value;
                    }

                    void increment(){
                        value++;
                    }

                    void decrement(){
                        value--;
                    }

                    ~JINT(){
                    }
                };
                map<JObject*,JINT*>* fromObject;
                map<JObject*,JINT*>* toObject;

            protected:
                JClass* _class;
                JObject(JClass* _class);
                JObject(jbool root);
                void link(JObject* o);
                void unlink(JObject* o);

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
                void finalize();
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
