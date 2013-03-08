#ifndef JPRIMITIVEDOUBLE_H
#define JPRIMITIVEDOUBLE_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveDouble : public JObject{

            protected:
                double value;

            public:
                JPrimitiveDouble();
                JPrimitiveDouble(double value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(double value);

                double get();

                string toString();

                virtual ~JPrimitiveDouble();
        };
    }
}

#endif // JPRIMITIVEDOUBLE_H