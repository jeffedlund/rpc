#ifndef JBYTE_H
#define JBYTE_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveByte.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JByte : public JNumber, public JComparable{

            protected:
                JPrimitiveByte* value;
                void setPrimitiveByte(JPrimitiveByte* value);
                JPrimitiveByte* getPrimitiveByte();
                friend class JByteClass;

            public:
                JByte();
                JByte(jbyte value);
                static JClass* getClazz();
                static jint hashCode(jbyte b);
                static jint compare(jbyte x,jbyte y);
                static jbyte MIN_VALUE;
                static jbyte MAX_VALUE;
                static JClass* TYPE;
                static jint toUnsignedInt(jbyte x);
                static jlong toUnsignedLong(jbyte x);
                static jint SIZE;
                static jint BYTES;
                JByte operator+=(jbyte f);
                JByte operator-=(jbyte f);
                JByte operator*=(jbyte f);
                void set(jbyte value);
                jbyte get();
                jbyte byteValue();
                jshort shortValue();
                jint intValue();
                jlong longValue();
                jfloat floatValue();
                jdouble doubleValue();
                virtual jint compareTo(JObject * o);
                virtual jint hashCode();
                virtual bool equals(JObject* other);
                virtual string toString();
                virtual ~JByte();
        };
    }
}

#endif // JBYTE_H
