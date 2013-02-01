#ifndef JLONG_H
#define JLONG_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JLong : public JNumber{

    protected:
        qint64 value;

    public:
        JLong();
        JLong(qint64 value);

        static JClass* getClazz();

        void set(qint64 value);

        qint64 get();

        string toString();

        ~JLong();
};

#endif // JLONG_H
