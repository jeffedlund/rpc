#ifndef JCHAR_H
#define JCHAR_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JPrimitiveChar.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JChar : public JObject, public JComparable{

            protected:
                JPrimitiveChar* value;

            public:
                JChar();
                JChar(char value);
                JChar(jchar value);
                static JClass* getClazz();
                static jint hashCode(jchar c);
                static jint compare(jchar x,jchar y);
                static jchar MIN_VALUE;
                static jchar MAX_VALUE;
                void set(char value);
                char get();
                void setPrimitiveChar(JPrimitiveChar* value);
                JPrimitiveChar* getPrimitiveChar();
                virtual jint compareTo(JObject * o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JChar();
        };
    }
}
#endif // JCHAR_H
