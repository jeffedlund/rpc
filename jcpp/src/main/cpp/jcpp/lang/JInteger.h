#ifndef JINTEGER_H
#define JINTEGER_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JInteger : public JNumber, public JComparable{

            protected:
                JPrimitiveInt* value;

            public:
                JInteger();
                JInteger(jint value);
                static JClass* getClazz();
                static jint hashCode(jint i);
                static jint compare(jint x,jint y);
                static jint MIN_VALUE;
                static jint MAX_VALUE;
                JInteger operator+=(jint f);
                JInteger operator-=(jint f);
                JInteger operator*=(jint f);
                void set(jint value);
                jint get();
                void setPrimitiveInt(JPrimitiveInt* value);
                JPrimitiveInt* getPrimitiveInt();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JInteger();
        };
    }
}

#endif // JINTEGER_H
