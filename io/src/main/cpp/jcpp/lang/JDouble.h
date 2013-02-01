#ifndef JDOUBLE_H
#define JDOUBLE_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JDouble : public JNumber{

    protected:
        double value;

    public:
        JDouble();
        JDouble(double value);

        static JClass* getClazz();

        void set(double value);

        double get();

        string toString();

        ~JDouble();
};

#endif // JDOUBLE_H
