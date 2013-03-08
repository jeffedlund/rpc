#ifndef JINTERFACE_H
#define JINTERFACE_H

#include <iostream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;

        class JCPP_LIBRARY_EXPORT JInterface{
            public:
                static JClass* getClazz();
                virtual ~JInterface();
        };
    }
}

#endif // JINTERFACE_H
