#ifndef JBOOLEAN_H
#define JBOOLEAN_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JPrimitiveBoolean.h"
#include "JCPP.h"
#include "JComparable.h"
#include "JSerializable.h"
#include "JString.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JBoolean : public JObject,public JComparable, public JSerializable{
           protected:
                JPrimitiveBoolean* value;
                void setPrimitiveBoolean(JPrimitiveBoolean* value);
                JPrimitiveBoolean* getPrimitiveBoolean();
                friend class JBooleanClass;

            public:
                JBoolean();
                JBoolean(jbool value);
                JBoolean(JPrimitiveBoolean* value);
                static JClass* getClazz();
                static JBoolean* TRUE;
                static JBoolean* FALSE;
                static JClass* TYPE;
                static jbool parseBoolean(JString s);
                static JBoolean* valueOf(jbool b);
                static JBoolean* valueOf(JString s);
                static JString toString(jbool b);
                static jint hashCode(jbool value);
                static jint compare(jbool v1,jbool v2);
                static jbool getBoolean(JString name);
                void set(jbool value);
                jbool get();
                jbool booleanValue();
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JBoolean();
        };
    }
}
#endif // JBOOLEAN_H
