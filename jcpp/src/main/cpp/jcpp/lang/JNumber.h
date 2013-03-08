#ifndef JNUMBER_H
#define JNUMBER_H

#include "JObject.h"
#include "JClass.h"
#include "JSerializable.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JNumber: public JObject{
            protected :
                JNumber(JClass* _class);

            public:

                static JClass* getClazz();

                virtual string toString()=0;

                virtual ~JNumber();

        };
    }
}
#endif // JNUMBER_H
