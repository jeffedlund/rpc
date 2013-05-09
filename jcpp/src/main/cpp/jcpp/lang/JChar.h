#ifndef JCHAR_H
#define JCHAR_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JPrimitiveChar.h"
#include "JCPP.h"
#include "JComparable.h"
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JChar : public JObject, public JComparable, public JSerializable{

            protected:
                JPrimitiveChar* value;
                void setPrimitiveChar(JPrimitiveChar* value);
                JPrimitiveChar* getPrimitiveChar();
                friend class JCharClass;

            public:
                JChar();
                JChar(char value);
                JChar(jchar value);
                static JClass* getClazz();
                static jint hashCode(jchar c);
                static jint compare(jchar x,jchar y);
                static jchar MIN_VALUE;
                static jchar MAX_VALUE;
                static JClass* TYPE;
                void set(jchar value);
                jchar get();
                jchar charValue();
                virtual jint compareTo(JObject * o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JChar();
        };
    }
}
#endif // JCHAR_H
