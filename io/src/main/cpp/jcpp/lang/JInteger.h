#ifndef JINTEGER_H
#define JINTEGER_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JInteger : public JNumber{

            protected:
                qint32 value;

            public:
                JInteger();
                JInteger(qint32 value);

                static JClass* getClazz();

                void set(qint32 value);

                qint32 get();

                string toString();

                ~JInteger();
        };
    }
}

#endif // JINTEGER_H
