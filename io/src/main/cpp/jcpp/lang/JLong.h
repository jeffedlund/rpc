#ifndef JLONG_H
#define JLONG_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JLong : public JObject{

    protected:
        qint64 value;

    public:
        JLong(qint64 value);

        static JClass* clazz;

        void set(qint64 value);

        qint64 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JLong();
};

#endif // JLONG_H
