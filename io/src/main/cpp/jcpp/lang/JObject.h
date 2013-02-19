#ifndef JOBJECT_H
#define JOBJECT_H

#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;

        class JObject{//TODO implement wait/notifyAll/lock/unlock

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

                ~JObject();
        };
    }
}
#endif // JOBJECT_H
