#ifndef JPRIMITIVEINT_H
#define JPRIMITIVEINT_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JPrimitiveInt : public JObject{

    protected:
        qint32 value;

    public:
        JPrimitiveInt(qint32 value);

        static JClass* clazz;

        void set(qint32 value);

        qint32 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JPrimitiveInt();
};

#endif // JPRIMITIVEINT_H
