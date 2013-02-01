#ifndef JNUMBER_H
#define JNUMBER_H

#include "JObject.h"
#include "JClass.h"
#include "JSerializable.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

class JNumber: public JObject{
    protected :
        JNumber(JClass* _class);

    public:

        static JClass* getClazz();

        virtual string toString()=0;

};
#endif // JNUMBER_H
