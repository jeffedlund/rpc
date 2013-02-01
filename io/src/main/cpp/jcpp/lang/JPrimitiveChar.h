#ifndef JPRIMITIVECHAR_H
#define JPRIMITIVECHAR_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JPrimitiveChar : public JObject{

    protected:
        char value;

    public:
        JPrimitiveChar();
        JPrimitiveChar(char value);

        static JClass* getClazz();

        void set(char value);

        char get();

        string toString();

        ~JPrimitiveChar();
};

#endif // JPRIMITIVECHAR_H
