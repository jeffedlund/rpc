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
#include "JCPP.h"

namespace jcpp{
    namespace io{
        class JObjectStreamClass;
        static const int NULL_HANDLE = -1;

        class JCPP_LIBRARY_EXPORT JObjectInputStream : public JInputStream, public JObjectStreamConstants{
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
            JObjectStreamClass* readClassDesc();
            JObjectStreamClass* readNonProxyDesc();
            JObjectStreamClass* readProxyDesc();
            JObject* readNull();
            JObject* readHandle();
            JObject* readClass();
            JObject* readArray();
            JObject* readEnum();
            JObject* readOrdinaryObject();
            JIOException* readFatalException();
            JObject* checkResolve(JObject*);
            JObject* readObject0();
            void clear();

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
            virtual JObject* readObject();
            virtual JString* readString();
            virtual JString* readTypeString();
            virtual void defaultReadObject();
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
