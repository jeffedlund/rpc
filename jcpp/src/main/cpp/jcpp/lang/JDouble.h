#ifndef JDOUBLE_H
#define JDOUBLE_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveDouble.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JDouble : public JNumber{

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

                virtual ~JDouble();
        };
    }
}

#endif // JDOUBLE_H
