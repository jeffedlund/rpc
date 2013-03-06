#ifndef JMETHOD_H
#define JMETHOD_H

#include "JObject.h"
#include "JAccessibleObject.h"
using namespace std;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JMethod : public JAccessibleObject{
            public:
                typedef JObject* (*invocation)(JObject* objet,vector<JObject*>*args);
            private:
                string name;
                JClass* declaringClass;
                JClass* returnType;
                vector<JClass*>* parameterType;
                invocation inv;

            public:
                JMethod(string name,JClass* declaringClass,JClass* returnType,vector<JClass*>* parameterType,invocation inv);
                static JClass* getClazz();

                string getName();

                JClass* getDeclaringClass();

                JClass* getReturnType();

                vector<JClass*>* getParameterType();

                JObject* invoke(JObject* object, vector<JObject*>*args);

                virtual string toString();

                virtual ~JMethod();
            };
        }
    }
}

#endif // JMETHOD_H
