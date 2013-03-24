#ifndef JPRIMITIVEFLOAT_H
#define JPRIMITIVEFLOAT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveFloat : public JObject, public JComparable{

            protected:
                jfloat value;

            public:
                JPrimitiveFloat();
                JPrimitiveFloat(float value);
                JPrimitiveFloat operator+=(jfloat f);
                JPrimitiveFloat operator-=(jfloat f);
                JPrimitiveFloat operator*=(jfloat f);
                static JClass* getClazz();
                void set(jfloat value);
                jfloat get();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JPrimitiveFloat();
        };
    }
}

#endif // JPRIMITIVEFLOAT_H
