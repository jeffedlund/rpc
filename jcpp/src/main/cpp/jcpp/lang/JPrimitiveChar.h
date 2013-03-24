#ifndef JPRIMITIVECHAR_H
#define JPRIMITIVECHAR_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveChar : public JObject, public JComparable{

            protected:
                jchar value;

            public:
                JPrimitiveChar();
                JPrimitiveChar(char value);
                JPrimitiveChar(jchar value);
                static JClass* getClazz();
                void set(jchar value);
                jchar get();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JPrimitiveChar();
        };
    }
}
#endif // JPRIMITIVECHAR_H
