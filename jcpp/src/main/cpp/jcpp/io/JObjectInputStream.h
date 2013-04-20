#ifndef JOBJECTINPUTSTREAM_H
#define JOBJECTINPUTSTREAM_H

class SerialCallbackContext;
#include "JInputStream.h"
#include "JObject.h"
#include "JObjectStreamConstants.h"
#include "JClassLoader.h"
#include "JClass.h"
#include "JObjectStreamClass.h"
#include "JString.h"
#include "JEnum.h"
#include "climits"
#include "memory.h"
#include "JBits.h"
#include "SerialCallbackContext.h"
#include "HandleList.h"
#include "HandleTable.h"
#include "JBlockDataInputStream.h"
#include "JIOException.h"
#include "JLANG.h"
#include "Object.h"
#include "JObjectInput.h"
#include "JCPP.h"

namespace jcpp{
    namespace io{
        class JObjectStreamClass;
        static const int NULL_HANDLE = -1;

        class JCPP_LIBRARY_EXPORT JObjectInputStream : public JInputStream, public JObjectInput, public JObjectStreamConstants{
        public:
            class JCPP_LIBRARY_EXPORT JGetField : public JObject{
            protected:
                JGetField(JClass* _class):JObject(_class){
                }

            public:
                static JClass* getClazz();
                virtual JObjectStreamClass* getObjectStreamClass()=0;
                virtual jbool defaulted(string name)=0;
                virtual jbool get(string name,jbool val)=0;
                virtual jbyte get(string name,jbyte val)=0;
                virtual jchar get(string name,jchar val)=0;
                virtual jshort get(string name,jshort val)=0;
                virtual jint get(string name,jint val)=0;
                virtual jlong get(string name,jlong val)=0;
                virtual jfloat get(string name,jfloat val)=0;
                virtual jdouble get(string name,jdouble val)=0;
                virtual JObject* get(string name,JObject* val)=0;
                virtual ~JGetField();
            };

        protected:
            JBlockDataInputStream *bin;
            JClassLoader* inputClassLoader;
            HandleTable* handles;
            jint passHandle;
            jbyte *primVals;
            bool enableResolve;
            SerialCallbackContext* curContext;

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
            JIOException* readFatalException();
            JObject* checkResolve(JObject*);
            JObject* readObject0(jbool unshared);
            void clear();
            friend class JGetFieldImpl;

        protected:
            bool enableResolveObject(bool enable);
            JClass *resolveClass(JObjectStreamClass* jObjectStreamClass);
            JClass *resolveProxyClass(string* str,int i);
            virtual JObject* resolveObject(JObject* jobject);
            JObjectInputStream(JInputStream* inputStrean,JClass* _class);
            void init(JInputStream* in);

        public:
            JObjectInputStream(JInputStream* inputStrean);

            void setInputClassLoader(JClassLoader* inputClassLoader);
            static JClass* getClazz();
            virtual void readFully(jbyte b[], jint off, jint len);
            virtual jint skipBytes(jint n);
            virtual jlong skip(jlong n);
            virtual jint readUnsignedByte();
            virtual jint readUnsignedShort();
            virtual JObject* readObject();
            virtual JString* readString(jbool unshared);
            virtual JString* readTypeString();
            virtual JObject* readUnshared();
            virtual void defaultReadObject();
            virtual JGetField* readFields();
            virtual jint available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jint read();
            virtual int read(jbyte b[], int off, int len);
            virtual jbyte readByte();
            virtual jint peek();
            virtual jchar readChar();
            virtual jdouble readDouble();
            virtual jfloat readFloat();
            virtual jint readInt();
            virtual jlong readLong();
            virtual jshort readShort();
            virtual jbool readBool();
            virtual JPrimitiveByte* readPrimitiveByte();
            virtual JPrimitiveChar* readPrimitiveChar();
            virtual JPrimitiveDouble* readPrimitiveDouble();
            virtual JPrimitiveFloat* readPrimitiveFloat();
            virtual JPrimitiveInt* readPrimitiveInt();
            virtual JPrimitiveLong* readPrimitiveLong();
            virtual JPrimitiveShort* readPrimitiveShort();
            virtual JPrimitiveBoolean* readPrimitiveBool();
            virtual string readUTF();
            virtual string readLongUTF();
            virtual void close();
            virtual ~JObjectInputStream();
        };
    }
}

#endif // JOBJECTINPUTSTREAM_H
