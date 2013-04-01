#ifndef JPRIMITIVEINT_H
#define JPRIMITIVEINT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveInt : public JObject, public JComparable, public JSerializable{

            protected:
                jint value;

            public:
                JPrimitiveInt();
                JPrimitiveInt(jint value);
                JPrimitiveInt(JPrimitiveInt* value);
                jbool operator<(JObject &other);
                JPrimitiveInt operator+=(jint f);
                JPrimitiveInt operator-=(jint f);
                JPrimitiveInt operator*=(jint f);
                static JClass* getClazz();
                void set(jint value);
                jint get();
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual JPrimitiveInt* clone();
                virtual ~JPrimitiveInt();
        };
    }
}

#endif // JPRIMITIVEINT_H
