#ifndef JINTERFACE_H
#define JINTERFACE_H

#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;

        class JInterface{
            public:
                static JClass* getClazz();
        };
    }
}

#endif // JINTERFACE_H
