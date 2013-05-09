#ifndef JMETHOD_H
#define JMETHOD_H

#include "JString.h"
#include "JObject.h"
#include "JAccessibleObject.h"
#include "JCPP.h"
#include "JMember.h"
using namespace std;
using namespace jcpp::lang;

//TODO fill modifiers for field/method
namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JMethod : public JAccessibleObject, public JMember{
            public:
                typedef JObject* (*invocation)(JObject* objet,vector<JObject*>*args);
            private:
                JString name;
                JClass* declaringClass;
                JClass* returnType;
                vector<JClass*>* parameterType;
                invocation inv;
                jint modifiers;

            public:
                JMethod(JString name,JClass* declaringClass,JClass* returnType,vector<JClass*>* parameterType,invocation inv);
                static JClass* getClazz();
                virtual JString getName();
                virtual JClass* getDeclaringClass();
                virtual jint getModifiers();
                virtual jbool isSynthetic();
                JClass* getReturnType();
                vector<JClass*>* getParameterType();
                JObject* invoke(JObject* object, vector<JObject*>*args);
                virtual bool equals(JObject* o);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JMethod();
            };
        }
    }
}

#endif // JMETHOD_H
