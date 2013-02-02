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

class JObjectStreamClass;

static const int NULL_HANDLE = -1;

class JObjectInputStream : public JInputStream, public JObjectStreamConstants{

    /** Data input stream */
    BlockDataInputStream *bin;

    /** class loader */
    JClassLoader* classLoader;

    /** wire handle -> obj/exception map */
    HandleTable* handles;
    /** scratch field for passing handle values up/down call stack */
    qint32 passHandle;
    /** flag set when at end of field value block with no TC_ENDBLOCKDATA */
    bool defaultDataEnd;

    /** buffer for reading primitive field values */
    qint8 *primVals;

    /** if true, invoke resolveObject() */
    bool enableResolve;

    /**
     * Context during upcalls to class-defined readObject methods; holds
     * object currently being deserialized and descriptor for current class.
     * Null when not during readObject upcall.
     */
    SerialCallbackContext curContext;

    void skipCustomData();

    void readSerialData(JObject*, JObjectStreamClass*);
    void defaultReadFields(JObject*, JObjectStreamClass*);

    JObjectStreamClass* readClassDesc();
    JObjectStreamClass* readNonProxyDesc();
    JObjectStreamClass* readProxyDesc();

    JObject* readNull();
    JObject* readHandle();
    JObject* readArray();
    JObject* readEnum();
    JObject* readOrdinaryObject();

    JObject* checkResolve(JObject*);

    JObject* readObject0();

    void clear();

protected:
    /**
     * Enable the stream to allow objects read from the stream to be replaced.
     * When enabled, the resolveObject method is called for every object being
     * deserialized.
     *
     * <p>If <i>enable</i> is true, and there is a security manager installed,
     * this method first calls the security manager's
     * <code>checkPermission</code> method with the
     * <code>SerializablePermission("enableSubstitution")</code> permission to
     * ensure it's ok to enable the stream to allow objects read from the
     * stream to be replaced.
     *
     * @param	enable true for enabling use of <code>resolveObject</code> for
     * 		every object being deserialized
     * @return	the previous setting before this method was invoked
     */
    bool enableResolveObject(bool enable);

    JClass *resolveClass(JObjectStreamClass* jObjectStreamClass);
    JClass *resolveProxyClass(string* str,int i);
    virtual JObject* resolveObject(JObject* jobject);

public:
    JObjectInputStream(JInputStream* inputStrean);

    void setClassLoader(JClassLoader* classLoader);

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

#endif // JOBJECTINPUTSTREAM_H
