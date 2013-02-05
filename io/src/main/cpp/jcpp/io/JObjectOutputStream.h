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

class SerialCallbackContext;
class ObjectStreamClass;
class JObjectOutputStream : public JOutputStream, public JObjectStreamConstants{
private:
    JBlockDataOutputStream* bout;
    OutputHandleTable* handles;
    JClassLoader* outputClassLoader;
    qint32 depth;
    qint8* primVals;
    bool enableOverride;
    bool enableReplace;
    SerialCallbackContext* curContext;

    void writeHandle(qint32 handle);

protected:
    virtual JObject* replaceObject(JObject *obj);

public:
    JObjectOutputStream();
    JObjectOutputStream(JOutputStream* out);

    JClassLoader* getOutputClassLoader();

    bool enableReplaceObject(bool enable);
    void writeByte(qint8 b);
    void writeChar(quint16 v);
    void writeShort(qint16 v);
    void writeInt(qint32 v);
    void writeLong(qint64 v);
    void writeFloat(float v);
    void writeDouble(double v);
    void writeBoolean(bool b);
    void writeUTF(string str);
    void writeChars(string str);
    void writeBytes(string str);
    void flush();
    void close();
    void writeObject(JObject* object);
    void writeObject0(JObject* object);
    void writeStreamHeader();
    void writeNull();
    void writeTypeString(string str);
    void writeString(string str, bool unshared = false);
    void writeOrdinaryObject(JObject* object, JObjectStreamClass* desc, bool unshared = false);
    void writeClassDesc(JObjectStreamClass* desc, bool unshared = false);
    void writeProxyDesc(JObjectStreamClass* desc, bool unshared = false);
    void writeNonProxyDesc(JObjectStreamClass* desc, bool unshared = false);
    void writeClassDescriptor(JObjectStreamClass* desc);
    void writeEnum(JObject* obj, JObjectStreamClass* desc);
    void writeArray(JObject* obj,JObjectStreamClass* desc, bool unshared = false);
    void writeArrayProperties(JObject* array);
    void writeSerialVersionUID();
    void writeSerialData(JObject* obj, JObjectStreamClass* desc);
    void defaultWriteObject();
    void defaultWriteFields(JObject* obj, JObjectStreamClass* desc);
    void writePrimitiveData(JObject* obj, JObjectStreamClass* desc);
    void writeObjectValues(JObject* obj, JObjectStreamClass* desc);
    virtual void writeObjectOverride(JObject* obj){}

    ~JObjectOutputStream();
};

#endif // JOBJECTOUTPUTSTREAM_H
