#ifndef JCLASS_H
#define JCLASS_H

#include "JObject.h"
#include "JMethod.h"
#include "JField.h"
class JEnum;
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
    vector<JEnum*>* enumConstants;
    map<string,JField*>* fields;
    vector<JField*>* fieldsList;
    map<string,JMethod*>* methods;
    vector<JMethod*>* methodsList;
    vector<JClass*>* interfaces;
    bool bIsArray;
    bool bIsProxy;
    bool bIsEnum;
    bool bIsInterface;
    bool bIsPrimitive;
    qint64 serialVersionUID;
    JClass(JClassLoader* classLoader);
    JClass();
    JClass(bool root);

    void addEnumConstant(JEnum* enumConstant);
    void addField(JField* field);
    void addMethod(JMethod* method);
    void addInterface(JClass* interface);

 public:

    static JClass* getClazz();

    string getCanonicalName();

    string getName();

    string getSimpleName();

    JClassLoader* getClassLoader();

    JClass* getComponentType();

    vector<JEnum*>* getEnumConstants();

    JEnum* valueOf(string value);

    JField* getField(string name);

    vector<JField*>* getFields();

    vector<JClass*>* getInterfaces();

    JMethod* getMethod(string name, vector<JClass*>* parameterTypes);

    vector<JMethod*>* getMethods();

    virtual JClass* getSuperclass()=0;

    bool isArray();

    bool isProxy();

    bool isEnum();

    bool isAssignableFrom(JClass* clazz);

    bool isInstance(JObject* object);

    bool isInterface();

    bool isPrimitive();

    virtual JObject* newInstance()=0;

    qint64 getSerialVersionUID();

    string toString();

    ~JClass();
};

#endif // JCLASS_H
