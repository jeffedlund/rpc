#ifndef JINTERFACE_H
#define JINTERFACE_H

class JClass;

#include <iostream>
using namespace std;

class JInterface{
    public:
        static JClass* getClazz();
};

#endif // JINTERFACE_H
