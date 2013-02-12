#ifndef JDOUBLE_H
#define JDOUBLE_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include "JPrimitiveDouble.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JDouble : public JNumber{

            protected:
                JPrimitiveDouble* value;

            public:
                JDouble();
                JDouble(double value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(double value);

                double get();

                void setPrimitiveDouble(JPrimitiveDouble* value);

                JPrimitiveDouble* getPrimitiveDouble();

                string toString();

                ~JDouble();
        };
    }
}

#endif // JDOUBLE_H
