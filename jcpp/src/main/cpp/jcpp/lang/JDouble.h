#ifndef JDOUBLE_H
#define JDOUBLE_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveDouble.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JDouble : public JNumber, public JComparable{

            protected:
                JPrimitiveDouble* value;

            public:
                JDouble();
                JDouble(jdouble value);
                static JClass* getClazz();
                static jdouble MIN_VALUE;
                static jdouble MAX_VALUE;
                static jint hashCode(jdouble);
                static jint compare(jdouble d1,jdouble d2);
                JDouble operator+=(jdouble f);
                JDouble operator-=(jdouble f);
                JDouble operator*=(jdouble f);
                void set(double value);
                double get();
                void setPrimitiveDouble(JPrimitiveDouble* value);
                JPrimitiveDouble* getPrimitiveDouble();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JDouble();
        };
    }
}

#endif // JDOUBLE_H
