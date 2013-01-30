#ifndef JBOOLEAN_H
#define JBOOLEAN_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JBoolean : public JObject{

    protected:
        bool value;

    public:
        JBoolean(bool value);

        static JClass* clazz;

        void set(bool value);

        bool get();

        qint64 getSerialVersionUID();

        string toString();

        ~JBoolean();
};

#endif // JBOOLEAN_H
