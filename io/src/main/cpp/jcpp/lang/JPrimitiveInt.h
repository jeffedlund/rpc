#ifndef JPRIMITIVEINT_H
#define JPRIMITIVEINT_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveInt : public JObject{

            protected:
                qint32 value;

            public:
                JPrimitiveInt();
                JPrimitiveInt(qint32 value);

                bool operator==(JPrimitiveInt &other);

                static JClass* getClazz();

                void set(qint32 value);

                qint32 get();

                string toString();

                ~JPrimitiveInt();
        };
    }
}

#endif // JPRIMITIVEINT_H
