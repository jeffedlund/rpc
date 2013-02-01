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
        JPrimitiveBoolean();
        JPrimitiveBoolean(bool value);

        static JClass* getClazz();

        void set(bool value);

        bool get();

        string toString();

        ~JPrimitiveBoolean();
};

#endif // JPRIMITIVEBOOLEAN_H
