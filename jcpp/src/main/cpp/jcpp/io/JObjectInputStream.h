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

            jbool enableResolveObject(jbool enable);
            JClass *resolveClass(JObjectStreamClass* jObjectStreamClass);
            JClass *resolveProxyClass(JString* str,jint i);
            virtual JObject* resolveObject(JObject* jobject);
            JObjectInputStream(JInputStream* inputStrean,JClass* _class);
            void init(JInputStream* in);
            void skipCustomData();
            void readExternalData(JObject*, JObjectStreamClass*);
            void readSerialData(JObject*, JObjectStreamClass*);
            void defaultReadFields(JObject*, JObjectStreamClass*);
            JObjectStreamClass* readClassDesc(jbool unshared);
            JObjectStreamClass* readNonProxyDesc(jbool unshared);
            JObjectStreamClass* readProxyDesc(jbool unshared);
            JObject* readNull();
            JObject* readHandle(jbool unshared);
            JObject* readClass(jbool unshared);
            JObject* readArray(jbool unshared);
            JObject* readEnum(jbool unshared);
            JObject* readOrdinaryObject(jbool unshared);
            JString* readString(jbool unshared);
            JString* readTypeString();
            virtual JString* readLongUTF();
            JIOException* readFatalException();
            JObject* checkResolve(JObject*);
            JObject* readObject0(jbool unshared);
            void clear();
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
