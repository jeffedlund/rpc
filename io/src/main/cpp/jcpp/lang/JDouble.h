#ifndef JDOUBLE_H
#define JDOUBLE_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JDouble : public JObject{

    protected:
        double value;

    public:
        JDouble(double value);

        static JClass* clazz;

        void set(double value);

        double get();

        qint64 getSerialVersionUID();

        string toString();

        ~JDouble();
};

#endif // JDOUBLE_H
