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
        JPrimitiveFloat();
        JPrimitiveFloat(float value);

        static JClass* getClazz();

        void set(float value);

        float get();

        string toString();

        ~JPrimitiveFloat();
};

#endif // JPRIMITIVEFLOAT_H
