#ifndef JOBJECTSTREAMCLASS_H
#define JOBJECTSTREAMCLASS_H

#include "JObject.h"
#include "JString.h"
#include "JInputStream.h"
#include "JObjectStreamConstants.h"
#include "JObjectInputStream.h"
#include "JClassNotFoundException.h"
using namespace std;

class JObjectInputStream;

class JObjectStreamClass : public JObject{
    struct Field {
        char type;
        string name;
        int offset;
    };
    string name;
    qint64 suid;
    bool isProxy;
    bool bIsEnum;
    bool serializable;
    bool externalizable;
    bool writeObjectData;
    bool blockExternalData;
    qint16 numFields;
    Field* fields;
    int primDataSize;
    int numObjFields;
    JObjectStreamClass* superDesc;
    JClassNotFoundException* resolveEx;
    JClass* jClass;
    JMethod* readObjectMethod;

    void computeFieldOffsets();

public:
    JObjectStreamClass();

    static JClass* getClazz();

    JClass* getJClass();
    bool isEnum();
    qint16 getNumFields();
    qint32 getNumObjFields();
    Field getField(int i);
    const char* getName();
    int getPrimDataSize();
    JObjectStreamClass* getSuperDesc();
    JClassNotFoundException* getResolveException();

    void setPrimFieldValues(JObject *obj,qint8 *buf);
    void setObjectFieldValues(JObject* jobject, JObject** values);

    void readNonProxy(JObjectInputStream* objectInputStream);
    void initNonProxy(JObjectStreamClass* const objectStreamClass,JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
    void initProxy(JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
    void invokeReadObject(JObject* objet, JObjectInputStream* in);

    JObject* newInstance();

    bool hasReadObjectMethod();
    bool hasWriteObjectData();
    bool isExternalizable();
    bool hasBlockExternalData();

    string toString();
    ~JObjectStreamClass();
};

#endif // JOBJECTSTREAMCLASS_H
