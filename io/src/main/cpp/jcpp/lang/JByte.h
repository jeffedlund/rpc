#ifndef JBYTE_H
#define JBYTE_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JByte : public JObject{

    protected:
        qint8 value;

    public:
        JByte(qint8 value);

        static JClass* clazz;

        void set(qint8 value);

        qint8 get();

        qint64 getSerialVersionUID();

        string toString();

        ~JByte();
};

#endif // JBYTE_H
