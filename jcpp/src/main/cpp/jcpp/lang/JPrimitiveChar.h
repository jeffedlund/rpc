#ifndef JPRIMITIVECHAR_H
#define JPRIMITIVECHAR_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
#include "JComparable.h"
#include "JSerializable.h"
#include "JPrimitiveArray.h"
#include "JString.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveChar : public JObject, public JComparable, public JSerializable{
            protected:
                jchar value;

            public:
                JPrimitiveChar();
                JPrimitiveChar(char value);
                JPrimitiveChar(jchar value);
                static JClass* getClazz();
                static JPrimitiveArray* toArray(JString str);//TODO do we keep them here?
                static JString fromArray(JPrimitiveArray* a);
                void set(jchar value);
                jchar get();
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JPrimitiveChar();
        };
    }
}
#endif // JPRIMITIVECHAR_H
