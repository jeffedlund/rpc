#ifndef JPRIMITIVEFLOAT_H
#define JPRIMITIVEFLOAT_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JPrimitiveFloat : public JObject{

    protected:
        float value;

    public:
        JPrimitiveFloat(float value);

        static JClass* clazz;

        void set(float value);

        float get();

        qint64 getSerialVersionUID();

        string toString();

        ~JPrimitiveFloat();
};

#endif // JPRIMITIVEFLOAT_H
