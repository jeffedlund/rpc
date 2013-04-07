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
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JObjectInputStream;
        class JObjectOutputStream;

        class JCPP_LIBRARY_EXPORT JObjectStreamClass : public JObject{
        public:
            class ClassDataSlot{
                public:
                    JObjectStreamClass* desc;
                    bool hasData;

                    ClassDataSlot(JObjectStreamClass* desc, bool hasData) {
                        this->desc = desc;
                        this->hasData = hasData;
                    }
            };

        private:
            string name;
            jlong suid;
            bool bIsProxy;
            bool bIsEnum;
            bool serializable;
            bool externalizable;
            bool writeObjectData;
            bool blockExternalData;
            vector<JObjectStreamField*>* fields;
            int primDataSize;
            int numObjFields;
            JObjectStreamClass* superDesc;
            JClassNotFoundException* resolveEx;
            JClass* jClass;
            JMethod* readObjectMethod;
            JMethod* writeObjectMethod;
            JMethod* writeReplaceMethod;
            vector<ClassDataSlot*>* dataLayout;

            void computeFieldOffsets();
            JObjectStreamClass* getVariantFor(JClass* cl);
            vector<ClassDataSlot*>* getClassDataLayout0();

        public:
            JObjectStreamClass();
            JObjectStreamClass(JClass* _class);
            static JClass* getClazz();
            static JObjectStreamClass* lookup(JClass* obj,bool all);

            JClass* getJClass();
            bool isEnum();
            bool isProxy();
            jshort getNumFields();
            jint getNumObjFields();
            JObjectStreamField* getField(int i);
            string getName();
            int getPrimDataSize();
            JObjectStreamClass* getSuperDesc();
            JClassNotFoundException* getResolveException();
            void setPrimFieldValues(JObject *obj,jbyte *buf);
            void writePrimFieldValues(JObject* obj,jbyte* buf,JObjectOutputStream* out);
            void getObjectFieldValues(JObject* jobject, JObject** values);
            void setObjectFieldValues(JObject* jobject, JObject** values);
            void readNonProxy(JObjectInputStream* objectInputStream);
            void initNonProxy(JObjectStreamClass* const objectStreamClass,JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
            void initProxy(JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
            void invokeReadObject(JObject* objet, JObjectInputStream* in);
            void invokeWriteObject(JObject* object, JObjectOutputStream* out);
            JObject* invokeWriteReplace(JObject* obj);
            void writeNonProxy(JObjectOutputStream* out);
            JObject* newInstance();
            bool hasReadObjectMethod();
            bool hasWriteObjectMethod();
            bool hasWriteObjectData();
            bool hasWriteReplaceMethod();
            bool isExternalizable();
            bool hasBlockExternalData();
            vector<ClassDataSlot*>* getClassDataLayout();
            vector<JObjectStreamClass*>* getHierarchy();
            string toString();
            virtual ~JObjectStreamClass();
        };
    }
}

#endif // JOBJECTSTREAMCLASS_H
