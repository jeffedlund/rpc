#ifndef JBOOLEAN_H
#define JBOOLEAN_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

//TODO fill JField for in/out marshalling
//TODO add more public methods for all JBool,JFloat,...
class JBoolean : public JObject{

    protected:
        bool value;

    public:
        JBoolean();
        JBoolean(bool value);

        static JClass* getClazz();

        void set(bool value);

        bool get();

        string toString();

        ~JBoolean();
};

#endif // JBOOLEAN_H
