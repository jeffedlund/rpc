#ifndef JPRIMITIVEINT_H
#define JPRIMITIVEINT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveInt : public JObject{

            protected:
                jint value;

            public:
                JPrimitiveInt();
                JPrimitiveInt(jint value);
                JPrimitiveInt(JPrimitiveInt* value);
                bool operator<(JObject &other);
                JPrimitiveInt operator+=(jint f);
                JPrimitiveInt operator-=(jint f);
                JPrimitiveInt operator*=(jint f);
                static JClass* getClazz();
                void set(jint value);
                jint get();
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                JPrimitiveInt* clone();
                virtual ~JPrimitiveInt();
        };
    }
}

#endif // JPRIMITIVEINT_H
