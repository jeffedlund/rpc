#ifndef JPRIMITIVEDOUBLE_H
#define JPRIMITIVEDOUBLE_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
#include "JComparable.h"
#include "JSerializable.h"
#include "JString.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveDouble : public JObject, public JComparable, public JSerializable{
            protected:
                jdouble value;

            public:
                JPrimitiveDouble();
                JPrimitiveDouble(jdouble value);
                JPrimitiveDouble& operator+=(jdouble f);
                JPrimitiveDouble& operator-=(jdouble f);
                JPrimitiveDouble& operator*=(jdouble f);
                static JClass* getClazz();
                void set(jdouble value);
                jdouble get();
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JPrimitiveDouble();
        };
    }
}

#endif // JPRIMITIVEDOUBLE_H
