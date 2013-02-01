#ifndef JMETHOD_H
#define JMETHOD_H

#include "JObject.h"

class JMethod : public JObject{
private:
    std::string name;
    JClass* declaringClass;
    JClass* returnType;
    std::vector<JClass>* parameterType;

public:
    static JClass* getClazz();

    JMethod(std::string name,JClass* declaringClass,JClass* returnType);

    std::string getName();

    JClass* getDeclaringClass();

    JClass* getReturnType();

    std::vector<JClass>* getParameterType();

    JObject* invoke(JObject* object, JObject *args[]);

    std::string toString();
};

#endif // JMETHOD_H
