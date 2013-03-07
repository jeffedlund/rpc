#ifndef JOBJECTOUTPUTSTREAM_H
#define JOBJECTOUTPUTSTREAM_H

#include <map>
#include "string.h"
#include "JObjectStreamClass.h"
#include "JObjectStreamConstants.h"
#include "BlockDataOutputStream.h"
#include "JClassLoader.h"
#include "JDataOutputStream.h"
#include "SerialCallbackContext.h"
#include "OutputHandleTable.h"
#include "JLANG.h"
#include "Object.h"
#include "JCPP.h"

namespace jcpp{
    namespace io{
        class SerialCallbackContext;
        class ObjectStreamClass;
        class JCPP_LIBRARY_EXPORT JObjectOutputStream : public JOutputStream, public JObjectStreamConstants{
        private:
            JBlockDataOutputStream* bout;
            OutputHandleTable* handles;
            JClassLoader* outputClassLoader;
            jint depth;
            jbyte* primVals;
            int lengthPrimVals;
            bool enableOverride;
            bool enableReplace;
            SerialCallbackContext* curContext;

            void init(JOutputStream* out);
            void writeHandle(jint handle);

        protected:
            virtual JObject* replaceObject(JObject *obj);
            JObjectOutputStream(JOutputStream* out,JClass* _class);

        public:
            JObjectOutputStream(JOutputStream* out);
            static JClass* getClazz();
            JClassLoader* getOutputClassLoader();

            virtual bool enableReplaceObject(bool enable);
            virtual void writeBoolean(JPrimitiveBoolean* b);
            virtual void writeByte(JPrimitiveByte* b);
            virtual void writeChar(JPrimitiveChar* c);
            virtual void writeDouble(JPrimitiveDouble* d);
            virtual void writeFloat(JPrimitiveFloat* f);
            virtual void writeLong(JPrimitiveLong* l);
            virtual void writeShort(JPrimitiveShort* s);
            virtual void writeInt(JPrimitiveInt* i);
            virtual void writeByte(jbyte b);
            virtual void write(jbyte b);
            virtual void write(jbyte b[], int off, int len);
            virtual void writeChar(jchar v);
            virtual void writeShort(jshort v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(jfloat v);
            virtual void writeDouble(jdouble v);
            virtual void writeBoolean(jbool b);
            virtual void writeUTF(string str);
            virtual void writeChars(string str);
            virtual void writeBytes(string str);
            virtual void flush();
            virtual void close();
            virtual void writeObject(JObject* object);
            virtual void writeObject0(JObject* object);
            virtual void writeStreamHeader();
            virtual void writeNull();
            virtual void writeTypeString(JString* str);
            virtual void writeString(JString* str);
            virtual void writeOrdinaryObject(JObject* object, JObjectStreamClass* desc);
            virtual void writeClass(JClass* cl);
            virtual void writeClassDesc(JObjectStreamClass* desc);
            virtual void writeProxyDesc(JObjectStreamClass* desc);
            virtual void writeNonProxyDesc(JObjectStreamClass* desc);
            virtual void writeClassDescriptor(JObjectStreamClass* desc);
            virtual void writeEnum(JObject* obj, JObjectStreamClass* desc);
            virtual void writeArray(JObject* obj,JObjectStreamClass* desc);
            virtual void writeArrayProperties(JObject* array);
            virtual void writeSerialVersionUID();
            virtual void writeExternalData(JObject* obj);
            virtual void writeSerialData(JObject* obj, JObjectStreamClass* desc);
            virtual void defaultWriteObject();
            virtual void defaultWriteFields(JObject* obj, JObjectStreamClass* desc);
            virtual void writeFatalException(JIOException* ex);
            virtual void writePrimitiveData(JObject* obj, JObjectStreamClass* desc);
            virtual void writeObjectValues(JObject* obj, JObjectStreamClass* desc);
            virtual void writeObjectOverride(JObject*){}

            virtual ~JObjectOutputStream();
        };
    }
}
#endif // JOBJECTOUTPUTSTREAM_H
