#ifndef JPRIMITIVEBYTE_H
#define JPRIMITIVEBYTE_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

/*
simplecharacter, character  =>char
simpledouble, double        =>double
simplefloat, float          =>float
simpleinteger, integer      =>qint32
simplelong, long            =>qint64
simpleshort, short          =>qint16

*/
class JPrimitiveByte : public JObject{

    protected:
        qint8 value;

    public:
        JPrimitiveByte(qint8 value);

        static JClass* clazz;

        void set(qint8 value);

        qint8 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JPrimitiveByte();
};

#endif // JPRIMITIVEBYTE_H
