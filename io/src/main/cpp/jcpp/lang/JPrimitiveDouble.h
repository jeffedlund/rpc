#ifndef JPRIMITIVEDOUBLE_H
#define JPRIMITIVEDOUBLE_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JPrimitiveDouble : public JObject{

    protected:
        double value;

    public:
        JPrimitiveDouble(double value);

        static JClass* clazz;

        void set(double value);

        double get();

        qint64 getSerialVersionUID();

        string toString();

        ~JPrimitiveDouble();
};

#endif // JPRIMITIVEDOUBLE_H
