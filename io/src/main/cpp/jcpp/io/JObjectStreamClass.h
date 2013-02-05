#ifndef JOBJECTSTREAMCLASS_H
#define JOBJECTSTREAMCLASS_H

#include "JObject.h"
#include "JString.h"
#include "JInputStream.h"
#include "JObjectStreamConstants.h"
#include "JObjectInputStream.h"
#include "JClassNotFoundException.h"
#include "JObjectStreamField.h"
#include "map"
using namespace std;

class JObjectInputStream;
class JObjectOutputStream;

class JObjectStreamClass : public JObject{
    string name;
    qint64 suid;
    bool bIsProxy;
    bool bIsEnum;
    bool serializable;
    bool externalizable;
    bool writeObjectData;
    bool blockExternalData;
    qint16 numFields;
    JObjectStreamField** fields;
    int primDataSize;
    int numObjFields;
    JObjectStreamClass* superDesc;
    vector<JObjectStreamClass*>* hierarchy;
    JClassNotFoundException* resolveEx;
    JClass* jClass;
    JMethod* readObjectMethod;
    JMethod* writeObjectMethod;

    void computeFieldOffsets();

public:
    JObjectStreamClass();
    JObjectStreamClass(JClass* _class);
    static JClass* getClazz();
    static JObjectStreamClass* lookup(JObject* obj);
    static string getClassSignature(JClass* _class);

    JClass* getJClass();
    bool isEnum();
    bool isProxy();
    qint16 getNumFields();
    qint32 getNumObjFields();
    JObjectStreamField* getField(int i);
    const char* getName();
    int getPrimDataSize();
    JObjectStreamClass* getSuperDesc();
    JClassNotFoundException* getResolveException();
    void setPrimFieldValues(JObject *obj,qint8 *buf);
    void getPrimFieldValues(JObject* obj,qint8* buf,JObjectOutputStream* out);
    void setObjectFieldValues(JObject* jobject, JObject** values);
    void readNonProxy(JObjectInputStream* objectInputStream);
    void initNonProxy(JObjectStreamClass* const objectStreamClass,JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
    void initProxy(JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
    void invokeReadObject(JObject* objet, JObjectInputStream* in);
    void writeNonProxy(JObjectOutputStream* out);
    JObject* newInstance();
    bool hasReadObjectMethod();
    bool hasWriteObjectMethod();
    bool hasWriteObjectData();
    bool isExternalizable();
    bool hasBlockExternalData();
    vector<JObjectStreamClass*>* getClassDataLayout();
    vector<JObjectStreamClass*>* getHierarchy();
    string toString();
    ~JObjectStreamClass();
};

#endif // JOBJECTSTREAMCLASS_H
