#ifndef JPRIMITIVEFLOAT_H
#define JPRIMITIVEFLOAT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
#include "JSerializable.h"
#include "JString.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveFloat : public JObject, public JComparable, public JSerializable{

            protected:
                jfloat value;

            public:
                JPrimitiveFloat();
                JPrimitiveFloat(jfloat value);
                JPrimitiveFloat operator+=(jfloat f);
                JPrimitiveFloat operator-=(jfloat f);
                JPrimitiveFloat operator*=(jfloat f);
                static JClass* getClazz();
                void set(jfloat value);
                jfloat get();
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JPrimitiveFloat();
        };
    }
}

#endif // JPRIMITIVEFLOAT_H
