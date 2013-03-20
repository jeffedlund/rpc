#ifndef JBYTE_H
#define JBYTE_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveByte.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JByte : public JNumber{

            protected:
                JPrimitiveByte* value;

            public:
                JByte();
                JByte(jbyte value);
                static JClass* getClazz();
                static jint hashCode(jbyte b);
                static jbyte MIN_VALUE;
                static jbyte MAX_VALUE;
                JByte operator+=(jbyte f);
                JByte operator-=(jbyte f);
                JByte operator*=(jbyte f);
                void set(jbyte value);
                jbyte get();
                void setPrimitiveByte(JPrimitiveByte* value);
                JPrimitiveByte* getPrimitiveByte();
                virtual jint hashCode();
                virtual bool equals(JObject* other);
                virtual string toString();
                virtual ~JByte();
        };
    }
}

#endif // JBYTE_H
