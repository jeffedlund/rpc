#ifndef JCHAR_H
#define JCHAR_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JChar : public JObject{

    protected:
        char value;

    public:
        JChar();
        JChar(char value);

        static JClass* getClazz();

        void set(char value);

        char get();

        string toString();

        ~JChar();
};

#endif // JCHAR_H
