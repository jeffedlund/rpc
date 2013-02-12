#ifndef JINTEGER_H
#define JINTEGER_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JInteger : public JNumber{

            protected:
                JPrimitiveInt* value;

            public:
                JInteger();
                JInteger(qint32 value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(qint32 value);

                qint32 get();

                void setPrimitiveInt(JPrimitiveInt* value);

                JPrimitiveInt* getPrimitiveInt();

                string toString();

                ~JInteger();
        };
    }
}

#endif // JINTEGER_H
