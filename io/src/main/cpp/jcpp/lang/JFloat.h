#ifndef JFLOAT_H
#define JFLOAT_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JFloat : public JNumber{

    protected:
        float value;

    public:
        JFloat();
        JFloat(float value);

        static JClass* getClazz();

        void set(float value);

        float get();

        string toString();

        ~JFloat();
};

#endif // JFLOAT_H
