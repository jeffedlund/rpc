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
                jdouble value;

            public:
                JPrimitiveDouble();
                JPrimitiveDouble(jdouble value);
                bool operator==(JObject &other);
                JPrimitiveDouble operator+=(jdouble f);
                JPrimitiveDouble operator-=(jdouble f);
                JPrimitiveDouble operator*=(jdouble f);

                static JClass* getClazz();

                void set(jdouble value);

                jdouble get();

                string toString();

                virtual ~JPrimitiveDouble();
        };
    }
}

#endif // JPRIMITIVEDOUBLE_H
