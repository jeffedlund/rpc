#ifndef JINTEGER_H
#define JINTEGER_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JInteger : public JObject{

    protected:
        qint32 value;

    public:
        JInteger(qint32 value);

        static JClass* clazz;

        void set(qint32 value);

        qint32 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JInteger();
};

#endif // JINTEGER_H
