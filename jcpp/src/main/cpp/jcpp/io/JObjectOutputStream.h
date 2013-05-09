#ifndef JOBJECTOUTPUTSTREAM_H
#define JOBJECTOUTPUTSTREAM_H

#include <map>
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
        class JCPP_LIBRARY_EXPORT JObjectOutputStream : public JOutputStream, public JObjectOutput, public JObjectStreamConstants{
        public:
            class JCPP_LIBRARY_EXPORT JPutField : public JObject{
            protected:
                JPutField(JClass* _class):JObject(_class){
                }
            public:
                static JClass* getClazz();
                virtual void put(JString name,jbool val)=0;
                virtual void put(JString name,jbyte val)=0;
                virtual void put(JString name,jchar val)=0;
                virtual void put(JString name,jshort val)=0;
                virtual void put(JString name,jint val)=0;
                virtual void put(JString name,jlong val)=0;
                virtual void put(JString name,jfloat val)=0;
                virtual void put(JString name,jdouble val)=0;
                virtual void put(JString name,JObject* val)=0;
                virtual void write(JObjectOutput* out)=0;
                virtual ~JPutField();
            };

        protected:
            JBlockDataOutputStream* bout;
            OutputHandleTable* handles;
            JClassLoader* outputClassLoader;
            jint depth;
            jbyte* primVals;
            jint lengthPrimVals;
            jbool enableOverride;
            jbool enableReplace;
            SerialCallbackContext* curContext;
            JPutField* curPut;

            JObjectOutputStream(JOutputStream* out,JClass* _class);
            virtual void init(JOutputStream* out);
            virtual JObject* replaceObject(JObject *obj);
            virtual jbool enableReplaceObject(jbool enable);
            virtual void writeObjectOverride(JObject*){}
            virtual void writeStreamHeader();
            virtual void writeClassDescriptor(JObjectStreamClass* desc);
            virtual void writeTypeString(JString* str);
            virtual void writeObject0(JObject* object,jbool unshared);
            virtual void writeNull();
            virtual void writeHandle(jint handle);
            virtual void writeClass(JClass* cl,jbool unshared);
            virtual void writeClassDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeProxyDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeNonProxyDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeString(JString* str,jbool unshared);
            virtual void writeArray(JObject* obj,JObjectStreamClass* desc,jbool unshared);
            virtual void writeArrayProperties(JObject* array);
            virtual void writeEnum(JObject* obj, JObjectStreamClass* desc,jbool unshared);
            virtual void writeOrdinaryObject(JObject* object, JObjectStreamClass* desc,jbool unshared);
            virtual void writeExternalData(JObject* obj);
            virtual void writeSerialData(JObject* obj, JObjectStreamClass* desc);
            virtual void defaultWriteFields(JObject* obj, JObjectStreamClass* desc);
            virtual void writeFatalException(JIOException* ex);
            virtual void writeSerialVersionUID();
            virtual void writePrimitiveData(JObject* obj, JObjectStreamClass* desc);
            virtual void writeObjectValues(JObject* obj, JObjectStreamClass* desc);
            friend class JPutFieldImpl;
            friend class JObjectStreamClass;

        public:
            JObjectOutputStream(JOutputStream* out);
            static JClass* getClazz();
            JClassLoader* getOutputClassLoader();//TODO use thread.getcontextCL()
            virtual void writeObject(JObject* object);
            virtual void writeUnshared(JObject* object);
            virtual void defaultWriteObject();
            virtual JPutField* putFields();
            virtual void writeFields();
            virtual void write(jint b);
            virtual void writeInt(JPrimitiveInt* i);
            virtual void write(jbyte b[], jint off, jint len);
            virtual void flush();
            virtual void close();
            virtual void writeBoolean(JPrimitiveBoolean* b);
            virtual void writeByte(JPrimitiveByte* b);
            virtual void writeChar(JPrimitiveChar* c);
            virtual void writeDouble(JPrimitiveDouble* d);
            virtual void writeFloat(JPrimitiveFloat* f);
            virtual void writeLong(JPrimitiveLong* l);
            virtual void writeShort(JPrimitiveShort* s);
            virtual void writeByte(jint b);
            virtual void writeChar(jint v);
            virtual void writeShort(jint v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(jfloat v);
            virtual void writeDouble(jdouble v);
            virtual void writeBoolean(jbool b);
            virtual void writeUTF(JString str);
            virtual void writeChars(JString str);
            virtual void writeBytes(JString str);
            virtual ~JObjectOutputStream();
        };
    }
}
#endif // JOBJECTOUTPUTSTREAM_H
