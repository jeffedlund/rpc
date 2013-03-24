#ifndef JLONG_H
#define JLONG_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveLong.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JLong : public JNumber, public JComparable{

            protected:
                JPrimitiveLong* value;

            public:
                JLong();
                JLong(jlong value);
                static JClass* getClazz();
                static jlong MIN_VALUE;
                static jlong MAX_VALUE;
                static jint hashCode(jlong l);
                static jint compare(jlong x,jlong y);
                JLong operator+=(jlong f);
                JLong operator-=(jlong f);
                JLong operator*=(jlong f);
                void set(jlong value);
                jlong get();
                void setPrimitiveLong(JPrimitiveLong* value);
                JPrimitiveLong* getPrimitiveLong();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JLong();
        };
    }
}

#endif // JLONG_H
