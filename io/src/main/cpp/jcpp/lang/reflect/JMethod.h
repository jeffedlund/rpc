#ifndef JMETHOD_H
#define JMETHOD_H

#include "JObject.h"
using namespace std;

class JMethod : public JObject{
private:
    string name;
    JClass* declaringClass;
    JClass* returnType;
    vector<JClass*>* parameterType;

protected:
    JMethod(string name,JClass* declaringClass,JClass* returnType,vector<JClass*>* parameterType);

public:
    static JClass* getClazz();

    string getName();

    JClass* getDeclaringClass();

    JClass* getReturnType();

    vector<JClass*>* getParameterType();

    virtual JObject* invoke(JObject* object, vector<JObject*>*args)=0;

    virtual string toString();
};

#endif // JMETHOD_H
