#ifndef JCLASS_H
#define JCLASS_H

#include "JObject.h"
#include "JMethod.h"
#include "JField.h"
#include "JClassLoader.h"
class JClassLoader;
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <QtGlobal>
using namespace std;

class JClass : public JObject{
 protected:
    string canonicalName;
    string name;
    string simpleName;
    JClassLoader* classLoader;
    JClass* componentType;
    vector<JObject*>* enumConstants;
    map<string,JField*>* fields;
    map<string,JMethod*>* methods;
    vector<JClass*>* interfaces;
    JClass* superClass;
    bool bIsArray;
    bool bIsProxy;
    bool bIsEnum;
    bool bIsInterface;
    bool bIsPrimitive;
    JClass(JClassLoader* classLoader);
    JClass();
    void setName(string name);

 public:

    static JClass* clazz;

    string getCanonicalName();

    string getName();

    string getSimpleName();

    JClassLoader* getClassLoader();

    JClass* getComponentType();

    vector<JObject*>* getEnumConstants();

    JField* getField(string name);

    vector<JField*>* getFields();

    vector<JClass*>* getInterfaces();

    JMethod* getMethod(string name, vector<JClass*>* parameterTypes);

    vector<JMethod*>* getMethods();

    JClass* getSuperclass();

    bool isArray();

    bool isProxy();

    bool isEnum();

    bool isAssignableFrom(JClass* clazz);

    bool isInstance(JObject* object);

    bool isInterface();

    bool isPrimitive();

    JObject* newInstance();

    qint64 getSerialVersionUID();

    string toString();

    ~JClass();
};

#endif // JCLASS_H
