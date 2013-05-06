#ifndef JOBJECTSTREAMCLASS_H
#define JOBJECTSTREAMCLASS_H

#include "JObject.h"
#include "JString.h"
#include "JInputStream.h"
#include "JObjectStreamConstants.h"
#include "JObjectOutputStream.h"
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

        //TODO check what should be public/protected
        class JCPP_LIBRARY_EXPORT JObjectStreamClass : public JObject{
        protected:
            class JCPP_LIBRARY_EXPORT ClassDataSlot{
                public:
                    JObjectStreamClass* desc;
                    jbool hasData;

                    ClassDataSlot(JObjectStreamClass* desc, jbool hasData) {
                        this->desc = desc;
                        this->hasData = hasData;
                    }
            };

            string name;
            jlong suid;
            jbool bIsProxy;
            jbool bIsEnum;
            jbool serializable;
            jbool externalizable;
            jbool writeObjectData;
            jbool blockExternalData;
            vector<JObjectStreamField*>* fields;
            jint primDataSize;
            jint numObjFields;
            JObjectStreamClass* localDesc;
            JObjectStreamClass* superDesc;
            JClassNotFoundException* resolveEx;
            JClass* jClass;
            JMethod* readObjectMethod;
            JMethod* writeObjectMethod;
            JMethod* writeReplaceMethod;
            vector<ClassDataSlot*>* dataLayout;

            JObjectStreamClass();
            JObjectStreamClass(JClass* _class);
            void computeFieldOffsets();
            JObjectStreamClass* getVariantFor(JClass* cl);
            vector<ClassDataSlot*>* getClassDataLayout0();
            void initProxy(JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
            void initNonProxy(JObjectStreamClass* const objectStreamClass,JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
            void readNonProxy(JObjectInputStream* objectInputStream);
            void writeNonProxy(JObjectOutputStream* out);
            JClassNotFoundException* getResolveException();
            JObjectStreamClass* getSuperDesc();
            JObjectStreamClass* getLocalDesc();
            JObjectStreamField* getField(jint i);
            vector<JObjectStreamField*>* getFields();
            JObjectStreamField* getField(string name,JClass* type);
            jbool isEnum();
            jbool isProxy();
            jbool hasReadObjectMethod();
            jbool hasWriteObjectMethod();
            jbool hasWriteObjectData();
            jbool hasWriteReplaceMethod();
            jbool isExternalizable();
            jbool hasBlockExternalData();
            JObject* newInstance();
            void invokeWriteObject(JObject* object, JObjectOutputStream* out);
            void invokeReadObject(JObject* objet, JObjectInputStream* in);
            JObject* invokeWriteReplace(JObject* obj);
            vector<ClassDataSlot*>* getClassDataLayout();
            vector<JObjectStreamClass*>* getHierarchy();
            jshort getNumFields();
            jint getNumObjFields();
            jint getPrimDataSize();
            void setPrimFieldValues(JObject *obj,jbyte *buf);
            void writePrimFieldValues(JObject* obj,jbyte* buf,JObjectOutputStream* out);
            void getObjectFieldValues(JObject* jobject, JObject** values);
            void setObjectFieldValues(JObject* jobject, JObject** values);
            friend class JObjectInputStream;
            friend class JObjectOutputStream;
            friend class JObjectStreamClassClass;
            friend class JGetFieldImpl;
            friend class JPutFieldImpl;

        public:
            static JClass* getClazz();
            static JObjectStreamClass* lookup(JClass* obj,jbool all);
            string getName();
            JClass* getJClass();
            string toString();
            virtual ~JObjectStreamClass();
        };
    }
}

#endif // JOBJECTSTREAMCLASS_H
