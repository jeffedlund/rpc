#ifndef JFLOAT_H
#define JFLOAT_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JFloat : public JObject{

    protected:
        float value;

    public:
        JFloat(float value);

        static JClass* clazz;

        void set(float value);

        float get();

        qint64 getSerialVersionUID();

        string toString();

        ~JFloat();
};

#endif // JFLOAT_H
