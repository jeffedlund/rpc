#ifndef JFIELD_H
#define JFIELD_H

#include "JAccessibleObject.h"
#include "JCPP.h"
#include "JMember.h"
#include "JString.h"
using namespace std;

//TODO isEnumConstant, toGenericString,getBoolean, getByte, getChar, getShort, getInt, getLong,
//getFloat, getDouble, +setters
namespace jcpp{
    namespace lang{
        class JObject;

        namespace reflect{
            class JCPP_LIBRARY_EXPORT JField: public JAccessibleObject, public JMember{
            public:
                typedef JObject* (*getter)(JObject* objet);
                typedef void (*setter)(JObject* object,JObject* value);

            protected:
                JString name;
                JClass* type;
                getter g;
                setter s;
                jint iModifiers;
                JClass* declaringClass;

            public:
                JField(JString name,JClass* type,JClass* declaringClass);
                JField(JString name,JClass* type,JClass* declaringClass,getter g,setter s);
                static JClass* getClazz();
                virtual JString getName();
                JClass* getType();
                virtual JObject* get(JObject* object);
                virtual void set(JObject* object, JObject* value);
                virtual JClass* getDeclaringClass();
                virtual jint getModifiers();
                virtual jbool isSynthetic();
                virtual bool equals(JObject* o);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JField();
            };
        }
    }
}
#endif // JFIELD_H
