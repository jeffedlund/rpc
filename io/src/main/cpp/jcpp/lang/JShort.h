#ifndef JSHORT_H
#define JSHORT_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JShort : public JNumber{

    protected:
        qint16 value;

    public:
        JShort();
        JShort(qint16 value);

        static JClass* getClazz();

        void set(qint16 value);

        qint16 get();

        string toString();

        ~JShort();
};

#endif // JSHORT_H

