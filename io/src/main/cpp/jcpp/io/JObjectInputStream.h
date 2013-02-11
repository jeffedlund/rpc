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
#include "BlockDataInputStream.h"
#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JObjectStreamClass;
        static const int NULL_HANDLE = -1;

        class JObjectInputStream : public JInputStream, public JObjectStreamConstants{
            BlockDataInputStream *bin;
            JClassLoader* inputClassLoader;
            HandleTable* handles;
            qint32 passHandle;
            bool defaultDataEnd;
            qint8 *primVals;
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

        public:
            JObjectInputStream(JInputStream* inputStrean);

            void setInputClassLoader(JClassLoader* inputClassLoader);
            static JClass* getClazz();
            virtual JObject* readObject();
            virtual JString* readString();
            virtual JString* readTypeString();
            virtual void defaultReadObject();
            virtual qint64 available();
            virtual bool waitForReadyRead(int = 30000);
            virtual int read();
            virtual int read(qint8 b[], int off, int len);
            virtual qint8 readByte();
            virtual char readChar();
            virtual double readDouble();
            virtual float readFloat();
            virtual qint32 readInt();
            virtual qint64 readLong();
            virtual qint16 readShort();
            virtual bool readBool();
            virtual string readUTF();
            virtual string readLongUTF();
            virtual void close();

            ~JObjectInputStream();
        };
    }
}

#endif // JOBJECTINPUTSTREAM_H
