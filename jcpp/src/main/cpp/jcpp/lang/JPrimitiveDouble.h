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
                JPrimitiveDouble operator+=(jdouble f);
                JPrimitiveDouble operator-=(jdouble f);
                JPrimitiveDouble operator*=(jdouble f);
                static JClass* getClazz();
                void set(jdouble value);
                jdouble get();
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JPrimitiveDouble();
        };
    }
}

#endif // JPRIMITIVEDOUBLE_H
