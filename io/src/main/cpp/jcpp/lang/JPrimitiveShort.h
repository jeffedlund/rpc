#ifndef JPRIMITIVESHORT_H
#define JPRIMITIVESHORT_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JPrimitiveShort : public JObject{

    protected:
        qint16 value;

    public:
        JPrimitiveShort(qint16 value);

        static JClass* clazz;

        void set(qint16 value);

        qint16 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JPrimitiveShort();
};

#endif // JPRIMITIVESHORT_H
