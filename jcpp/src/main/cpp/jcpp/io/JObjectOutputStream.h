#ifndef JOBJECTOUTPUTSTREAM_H
#define JOBJECTOUTPUTSTREAM_H

#include <map>
#include "string.h"
#include "JObjectStreamClass.h"
#include "JObjectStreamConstants.h"
#include "JBlockDataOutputStream.h"
#include "JClassLoader.h"
#include "JDataOutputStream.h"
#include "SerialCallbackContext.h"
#include "OutputHandleTable.h"
#include "JLANG.h"
#include "Object.h"
#include "JCPP.h"
#include "JObjectOutput.h"
#include "JIOException.h"

namespace jcpp{
    namespace io{
        class SerialCallbackContext;
        class ObjectStreamClass;
        //TODO move some methods to protected and use friends to solve it. same for ObjectIStream
        class JCPP_LIBRARY_EXPORT JObjectOutputStream : public JOutputStream, public JObjectOutput, public JObjectStreamConstants{
        public:
            class JCPP_LIBRARY_EXPORT JPutField : public JObject{
            protected:
                JPutField(JClass* _class):JObject(_class){
                }
            public:
                static JClass* getClazz();
                virtual void put(string name,jbool val)=0;
                virtual void put(string name,jbyte val)=0;
                virtual void put(string name,jchar val)=0;
                virtual void put(string name,jshort val)=0;
                virtual void put(string name,jint val)=0;
                virtual void put(string name,jlong val)=0;
                virtual void put(string name,jfloat val)=0;
                virtual void put(string name,jdouble val)=0;
                virtual void put(string name,JObject* val)=0;
                virtual void write(JObjectOutput* out)=0;
                virtual ~JPutField();
            };

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
            JPutField* curPut;

            void init(JOutputStream* out);
            void writeHandle(jint handle);

        protected:
            virtual JObject* replaceObject(JObject *obj);
            JObjectOutputStream(JOutputStream* out,JClass* _class);
            friend class JPutFieldImpl;

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
            virtual void writeByte(jint b);
            virtual void write(jint b);
            virtual void write(jbyte b[], int off, int len);
            virtual void writeChar(jint v);
            virtual void writeShort(jint v);
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
            virtual void writeUnshared(JObject* object);
            virtual void writeObject(JObject* object);
            virtual void writeObject0(JObject* object,jbool unshared);
            virtual void writeStreamHeader();
            virtual void writeNull();
            virtual void writeTypeString(JString* str);
            virtual void writeString(JString* str,jbool unshared);
            virtual void writeOrdinaryObject(JObject* object, JObjectStreamClass* desc,jbool unshared);
            virtual void writeClass(JClass* cl,jbool unshared);
            virtual void writeClassDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeProxyDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeNonProxyDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeClassDescriptor(JObjectStreamClass* desc);
            virtual void writeEnum(JObject* obj, JObjectStreamClass* desc,jbool unshared);
            virtual void writeArray(JObject* obj,JObjectStreamClass* desc,jbool unshared);
            virtual void writeArrayProperties(JObject* array);
            virtual void writeSerialVersionUID();
            virtual void writeExternalData(JObject* obj);
            virtual void writeSerialData(JObject* obj, JObjectStreamClass* desc);
            virtual void defaultWriteObject();
            virtual JPutField* putFields();
            virtual void writeFields();
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
