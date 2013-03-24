#ifndef JBOOLEAN_H
#define JBOOLEAN_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JPrimitiveBoolean.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JBoolean : public JObject,public JComparable{

            protected:
                JPrimitiveBoolean* value;

            public:
                JBoolean();
                JBoolean(bool value);
                JBoolean(JPrimitiveBoolean* value);
                static JClass* getClazz();
                static jint hashCode(bool value);
                static jint compare(jbool v1,jbool v2);
                void set(bool value);
                bool get();
                void setPrimitiveBoolean(JPrimitiveBoolean* value);
                JPrimitiveBoolean* getPrimitiveBoolean();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JBoolean();
        };
    }
}
#endif // JBOOLEAN_H
