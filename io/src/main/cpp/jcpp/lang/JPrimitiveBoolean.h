#ifndef JPRIMITIVEBOOLEAN_H
#define JPRIMITIVEBOOLEAN_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JPrimitiveBoolean : public JObject{

    protected:
        bool value;

    public:
        JPrimitiveBoolean(bool value);

        static JClass* clazz;

        void set(bool value);

        bool get();

        qint64 getSerialVersionUID();

        string toString();

        ~JPrimitiveBoolean();
};

#endif // JPRIMITIVEBOOLEAN_H
