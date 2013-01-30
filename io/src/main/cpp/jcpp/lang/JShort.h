#ifndef JSHORT_H
#define JSHORT_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JShort : public JObject{

    protected:
        qint16 value;

    public:
        JShort(qint16 value);

        static JClass* clazz;

        void set(qint16 value);

        qint16 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JShort();
};

#endif // JSHORT_H
