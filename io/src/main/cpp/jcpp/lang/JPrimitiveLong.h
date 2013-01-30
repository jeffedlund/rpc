#ifndef JPRIMITIVELONG_H
#define JPRIMITIVELONG_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JPrimitiveLong : public JObject{

    protected:
        qint64 value;

    public:
        JPrimitiveLong(qint64 value);

        static JClass* clazz;

        void set(qint64 value);

        qint64 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JPrimitiveLong();
};

#endif // JPRIMITIVELONG_H
