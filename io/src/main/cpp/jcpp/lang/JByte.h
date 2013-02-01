#ifndef JBYTE_H
#define JBYTE_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JByte : public JNumber{

    protected:
        qint8 value;

    public:
        JByte();
        JByte(qint8 value);

        static JClass* getClazz();

        void set(qint8 value);

        qint8 get();

        string toString();

        ~JByte();
};

#endif // JBYTE_H
