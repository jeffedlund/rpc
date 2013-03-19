#ifndef JINTEGER_H
#define JINTEGER_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JInteger : public JNumber{

            protected:
                JPrimitiveInt* value;

            public:
                JInteger();
                JInteger(jint value);
                bool operator==(JObject &other);
                JInteger operator+=(jint f);
                JInteger operator-=(jint f);
                JInteger operator*=(jint f);
                static JClass* getClazz();
                static jint MIN_VALUE;
                static jint MAX_VALUE;
                void set(jint value);
                jint get();
                void setPrimitiveInt(JPrimitiveInt* value);
                JPrimitiveInt* getPrimitiveInt();
                string toString();
                virtual ~JInteger();
        };
    }
}

#endif // JINTEGER_H
