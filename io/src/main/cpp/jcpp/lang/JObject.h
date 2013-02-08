#ifndef JOBJECT_H
#define JOBJECT_H

class JClass;

#include <vector>
#include <iostream>
using namespace std;

class JObject{

    protected:
        JClass* _class;
        JObject(JClass* _class);
        JObject(bool root);

    public:
        JObject();

        static JClass* getClazz();

        JClass* getClass();

        virtual string toString();

        ~JObject();
};

#endif // JOBJECT_H
