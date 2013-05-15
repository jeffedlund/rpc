#ifndef JOBJECTINPUTSTREAM_H
#define JOBJECTINPUTSTREAM_H

class SerialCallbackContext;
#include "JInputStream.h"
#include "JObject.h"
#include "JObjectStreamConstants.h"
#include "JClassLoader.h"
#include "JClass.h"
#include "JObjectStreamClass.h"
#include "JEnum.h"
#include "climits"
#include "memory.h"
#include "JBits.h"
#include "SerialCallbackContext.h"
#include "HandleList.h"
#include "HandleTable.h"
#include "JBlockDataInputStream.h"
#include "JIOException.h"
#include "Object.h"
#include "JObjectInput.h"
#include "JCPP.h"

namespace jcpp{
    namespace lang{
        class JString;
    }
    namespace io{
        class JObjectStreamClass;
        static const jint NULL_HANDLE = -1;

        class JCPP_LIBRARY_EXPORT JObjectInputStream : public JInputStream, public JObjectInput, public JObjectStreamConstants{
        public:
            class JCPP_LIBRARY_EXPORT JGetField : public JObject{
            protected:
                JGetField(JClass* _class):JObject(_class){
                }

            public:
                static JClass* getClazz();
                virtual JObjectStreamClass* getObjectStreamClass()=0;
                virtual jbool defaulted(JString name)=0;
                virtual jbool get(JString name,jbool val)=0;
                virtual jbyte get(JString name,jbyte val)=0;
                virtual jchar get(JString name,jchar val)=0;
                virtual jshort get(JString name,jshort val)=0;
                virtual jint get(JString name,jint val)=0;
                virtual jlong get(JString name,jlong val)=0;
                virtual jfloat get(JString name,jfloat val)=0;
                virtual jdouble get(JString name,jdouble val)=0;
                virtual JObject* get(JString name,JObject* val)=0;
                virtual ~JGetField();
            };

        protected:
            JBlockDataInputStream *bin;
            JClassLoader* inputClassLoader;
            HandleTable* handles;
            jint passHandle;
            jbyte *primVals;
            jbool enableResolve;
            SerialCallbackContext* curContext;

            JObjectInputStream(JInputStream* inputStrean,JClass* _class);
            virtual jbool enableResolveObject(jbool enable);
            virtual JClass *resolveClass(JObjectStreamClass* jObjectStreamClass);
            virtual JClass *resolveProxyClass(JString* str,jint i);
            virtual JObject* resolveObject(JObject* jobject);
            virtual void init(JInputStream* in);
            virtual void skipCustomData();
            virtual void readExternalData(JObject*, JObjectStreamClass*);
            virtual void readSerialData(JObject*, JObjectStreamClass*);
            virtual void defaultReadFields(JObject*, JObjectStreamClass*);
            virtual JObjectStreamClass* readClassDesc(jbool unshared);
            virtual JObjectStreamClass* readNonProxyDesc(jbool unshared);
            virtual JObjectStreamClass* readProxyDesc(jbool unshared);
            virtual JObject* readNull();
            virtual JObject* readHandle(jbool unshared);
            virtual JObject* readClass(jbool unshared);
            virtual JObject* readArray(jbool unshared);
            virtual JObject* readEnum(jbool unshared);
            virtual JObject* readOrdinaryObject(jbool unshared);
            virtual JString* readString(jbool unshared);
            virtual JString* readTypeString();
            virtual JString* readLongUTF();
            virtual JIOException* readFatalException();
            virtual JObject* checkResolve(JObject*);
            virtual JObject* readObject0(jbool unshared);
            virtual void clear();
            friend class JGetFieldImpl;
            friend class JObjectStreamClass;

        public:
            JObjectInputStream(JInputStream* inputStrean);
            void setInputClassLoader(JClassLoader* inputClassLoader);//TODO use Thread.getContextClassLoader()
            static JClass* getClazz();
            virtual JObject* readObject();
            virtual JObject* readUnshared();
            virtual void defaultReadObject();
            virtual JGetField* readFields();//TODO check when the return is deleted
            virtual jint peek();
            virtual jint read();
            virtual jint read(jbyte b[], jint off, jint len);
            virtual jint available();
            virtual void close();
            virtual jbool readBool();
            virtual JPrimitiveBoolean* readPrimitiveBool();
            virtual jbyte readByte();
            virtual JPrimitiveByte* readPrimitiveByte();
            virtual jint readUnsignedByte();
            virtual jchar readChar();
            virtual JPrimitiveChar* readPrimitiveChar();
            virtual jshort readShort();
            virtual jint readUnsignedShort();
            virtual JPrimitiveShort* readPrimitiveShort();
            virtual jint readInt();
            virtual JPrimitiveInt* readPrimitiveInt();
            virtual jlong readLong();
            virtual JPrimitiveLong* readPrimitiveLong();
            virtual jfloat readFloat();
            virtual JPrimitiveFloat* readPrimitiveFloat();
            virtual jdouble readDouble();
            virtual JPrimitiveDouble* readPrimitiveDouble();
            virtual void readFully(jbyte b[], jint off, jint len);
            virtual jint skipBytes(jint n);
            virtual jlong skip(jlong n);
            virtual JString* readUTF();
            virtual ~JObjectInputStream();
        };
    }
}

#endif // JOBJECTINPUTSTREAM_H
