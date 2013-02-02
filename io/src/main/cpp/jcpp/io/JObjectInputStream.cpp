#include "JObjectInputStream.h"
#include <stack>
#include "JObject.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JStreamCorruptedException.h"
#include "JOptionalDataException.h"
#include "JNotActiveException.h"
#include "JInvalidClassException.h"
#include "JInternalError.h"
#include "JPrimitiveArray.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveShort.h"
#include <cstdio>
#include <QtGlobal>
#include <QList>
#include <sstream>

using namespace std;

class JObjectInputStreamClass : public JClass{
public:
    JObjectInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.io.ObjectInputStream";
        name="java.io.ObjectInputStream";
        simpleName="ObjectInputStream";
    }

    JClass* getSuperclass(){
        return JInputStream::getClazz();
    }

    JObject* newInstance(){
        throw new JInstantiationException("cannot instantiate object of class "+getName());
    }
};

static JClass* clazz;

JClass* JObjectInputStream::getClazz(){
    if (clazz==NULL){
        clazz=new JObjectInputStreamClass();
    }
    return clazz;
}

JObjectInputStream::JObjectInputStream(JInputStream *in):JInputStream(getClazz()){
    bin = new BlockDataInputStream(in);
    passHandle = NULL_HANDLE;
    handles = new HandleTable(100);
    primVals = NULL;
    defaultDataEnd  = false;

    // check stream header
    qint16 s0 = readShort();
    qint16 s1 = readShort();
    if (s0 != STREAM_MAGIC || s1 != STREAM_VERSION) {
        stringstream ss;
        ss<<"invalid stream header "<<s0<<","<<s1;
        throw new JStreamCorruptedException(ss.str());
    }
    bin->setBlockDataMode(true);
}

void JObjectInputStream::setClassLoader(JClassLoader* classLoader){
    this->classLoader=classLoader;
}

JObjectInputStream::~JObjectInputStream() {
    delete handles;
    delete bin;
}

qint64 JObjectInputStream::available() {
    return bin->available();
}

bool JObjectInputStream::waitForReadyRead(int i) {
    return bin->waitForReadyRead(i);
}

bool JObjectInputStream::enableResolveObject(bool enable) {
    if (enable == enableResolve) {
        return enable;
    }
    enableResolve = enable;
    return !enableResolve;
}

JObject* JObjectInputStream::readObject() {
    //TODO enableOverrid+other stuff
    return readObject0();
}

JObject* JObjectInputStream::readObject0() {
    bool oldMode = bin->getBlockDataMode();
    if (oldMode) {
        int remain = bin->currentBlockRemaining();
        if (remain > 0) {
            stringstream ss;
            ss<<remain;
            throw new JOptionalDataException(ss.str());
        }
        bin->setBlockDataMode(false);
    }

    qint8 tc;
    while ((tc = bin->peekByte()) == TC_RESET) {
        tc = bin->readByte();
        clear();
    }

    JObject* obj = NULL;
    switch (tc) {
    case TC_NULL:
        obj = readNull();
        break;

    case TC_REFERENCE:
        obj = readHandle();
        break;

    //TODO case TC_CLASS, TC_CLASSDESC, TC_PROXYCLASSDESC
    case TC_STRING:
    case TC_LONGSTRING:
        obj = checkResolve(readString());
        break;

    case TC_ARRAY:
        obj = checkResolve(readArray());
        break;

    case TC_ENUM:
        obj = checkResolve(readEnum());
        break;

    case TC_OBJECT:
        obj = checkResolve(readOrdinaryObject());
        break;

    //TODO case TC_Exception
    //TODO case TC_BLOCKDATALONG

    case TC_ENDBLOCKDATA:
        if (oldMode) {
            throw new JOptionalDataException();
        } else {
            throw new JStreamCorruptedException("unexpected end of block data");
        }
        break;

    default:
        bin->setBlockDataMode(oldMode);
        stringstream ss;
        ss<<"invalid type code:"<<tc;
        throw new JStreamCorruptedException(ss.str());
    }
    bin->setBlockDataMode(oldMode);
    return obj;
}

JObject* JObjectInputStream::checkResolve(JObject *obj) {
    if (!enableResolve) {//TODO lookup exception
        return obj;
    }
    JObject* rep = resolveObject(obj);
    if (rep != obj) {
        handles->setObject(passHandle, rep);
    }
    return rep;
}

JString* JObjectInputStream::readTypeString() {
    qint8 tc = bin->peekByte();
    switch (tc) {
    case TC_STRING:
    case TC_LONGSTRING:
        return readString();

    case TC_NULL:
        return (JString*) (readNull());

    case TC_REFERENCE:
        return (JString*) (readHandle());

    default:
        stringstream ss;
        ss<<"stream corrupted: invalid typecode "<<tc;
        throw new JStreamCorruptedException(ss.str());
    }
}

void JObjectInputStream::defaultReadObject() {
    if (!curContext.isUpcall()) {
        throw new JNotActiveException("not in call to readObject");
    }
    JObject* curObj = curContext.getObj();
    JObjectStreamClass* curDesc = curContext.getDesc();
    bin->setBlockDataMode(false);
    defaultReadFields(curObj, curDesc);
    bin->setBlockDataMode(true);
    if (!curDesc->hasWriteObjectData()) {
        defaultDataEnd = true;
    }
    //TODO check ClassNotFoundException
}

JObject* JObjectInputStream::resolveObject(JObject *obj) {
    return obj;
}

JObject* JObjectInputStream::readNull() {
    if (bin->readByte() != TC_NULL) {
        throw new JInternalError();
    }
    passHandle = NULL_HANDLE;
    return NULL;
}

JObject* JObjectInputStream::readHandle() {
    if (bin->readByte() != TC_REFERENCE) {
        throw new JInternalError();
    }
    passHandle = bin->readInt() - baseWireHandle;
    if (passHandle < 0 || passHandle >= handles->getSize()) {
        throw new JStreamCorruptedException("invalid handle value");
    }

    JObject* obj = handles->lookupObject(passHandle);
    return obj;
}

JObject* JObjectInputStream::readArray(){
    if (bin->readByte() != TC_ARRAY) {
        throw new JInternalError();
    }

    JObjectStreamClass* desc = readClassDesc();
    int len = bin->readInt();

    JPrimitiveArray* pArray = NULL;
    JClass* cl=desc->getJClass();
    JClass* ccl=NULL;
    if (cl != NULL) {
        ccl = cl->getComponentType();
        pArray = new JPrimitiveArray(ccl,len);
    }

    int arrayHandle = handles->assign(pArray);
    //TODO handle ResolveException ...

    if(ccl==NULL) {
        for (int i = 0; i < len; i++) {
            readObject0();
        }
    }else if (ccl->isPrimitive()){
        if (ccl == JPrimitiveByte::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveByte(readByte()));
            }

        }else if (ccl==JPrimitiveChar::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveChar(readChar()));
            }

        }else if (ccl==JPrimitiveDouble::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveDouble(readDouble()));
            }

        }else if (ccl==JPrimitiveFloat::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveFloat(readFloat()));
            }

        }else if (ccl == JPrimitiveInt::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveInt(readInt()));
            }

        }else if (ccl==JPrimitiveLong::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveLong(readLong()));
            }

        }else if (ccl==JPrimitiveShort::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveShort(readShort()));
            }

        }else if (ccl==JPrimitiveBoolean::getClazz()) {
            for (int i = 0; i < len; ++i) {
                pArray->set(i,new JPrimitiveBoolean(readBool()));
            }

        }else {
            throw new JInternalError();
        }
    }else{
        for (int i = 0 ; i < len; ++i) {
            pArray->set(i,readObject0());
        }
        //TODO handle.markDependency
    }

    handles->finish(arrayHandle);
    passHandle = arrayHandle;
    return pArray;
}

JObject* JObjectInputStream::readEnum() {
    if (bin->readByte() != TC_ENUM) {
        throw new JInternalError();
    }
    JObjectStreamClass* desc = readClassDesc();
    if (!desc->isEnum()){
        throw new JInvalidClassException("non-enum class: " + desc->toString());
    }

    int enumHandle = handles->assign(NULL);
    //TODO handle exception

    JString* mname = readString();
    string name = mname->getString();
    JEnum* en = desc->getJClass()->valueOf(name);
    handles->finish(enumHandle);
    passHandle = enumHandle;
    return en;
}

JObjectStreamClass* JObjectInputStream::readClassDesc() {
    qint8 tc = bin->peekByte();

    switch (tc) {
    case TC_NULL:
        return (JObjectStreamClass*) (readNull());

    case TC_REFERENCE:
        return (JObjectStreamClass*) (readHandle());

    case TC_CLASSDESC:
        return readNonProxyDesc();

    case TC_PROXYCLASSDESC:
        return readProxyDesc();

    default:
        stringstream ss;
        ss<<"invalid type code: "<<tc;
        throw new JStreamCorruptedException(ss.str());
    }
}

JObjectStreamClass* JObjectInputStream::readProxyDesc() {
    if (bin->readByte() != TC_PROXYCLASSDESC) {
        throw new JInternalError();
    }
    JObjectStreamClass* desc = new JObjectStreamClass;
    qint32 descHandle = handles->assign(desc);
    passHandle = NULL_HANDLE;

    int numIfaces = bin->readInt();
    string *ifaces = new string[numIfaces];
    for (int i = 0; i < numIfaces; ++i) {
        ifaces[i] = bin->readUTF();
    }

    bin->setBlockDataMode(true);
    JClass *metaObj = resolveProxyClass(ifaces,numIfaces);

    skipCustomData();

    desc->initProxy(metaObj, readClassDesc());

    handles->finish(descHandle);
    passHandle = descHandle;

    delete ifaces;
    delete metaObj;

    return desc;
}

JObjectStreamClass* JObjectInputStream::readNonProxyDesc() {
    if (bin->readByte() != TC_CLASSDESC) {
        throw new JInternalError();
    }
    JObjectStreamClass* desc = new JObjectStreamClass;
    qint32 descHandle = handles->assign(desc);
    passHandle = NULL_HANDLE;

    //TODO factoriser en readClassDescriptor
    JObjectStreamClass *readDesc = new JObjectStreamClass;
    readDesc->readNonProxy(this);

    JClass *metaObj = resolveClass(readDesc);

    skipCustomData();

    desc->initNonProxy(readDesc, metaObj, readClassDesc());

    handles->finish(descHandle);
    passHandle = descHandle;

    delete readDesc;
    delete metaObj;

    return desc;
}

JObject* JObjectInputStream::readOrdinaryObject() {
    if (bin->readByte() != TC_OBJECT) {
        throw new JInternalError();
    }
    JObjectStreamClass* desc = readClassDesc();
    //TODO check deserialize

    JObject* obj = desc->newInstance();
    passHandle = handles->assign(obj);

    //TODO handle exception

    //TODO do serializable+externalizable
    readSerialData(obj, desc);

    handles->finish(passHandle);

    //TODO handle exception + clone + handle.setObject???

    return obj;
}

/**
 * Reads in values of serializable fields declared by given class
 * descriptor. If obj is non-null, sets field values in obj.  Expects that
 * passHandle is set to obj's handle before this method is called.
 */
void JObjectInputStream::readSerialData(JObject *obj, JObjectStreamClass *desc) {

    QList<JObjectStreamClass*> list;
    for (JObjectStreamClass *d = desc; d != NULL; d = d->getSuperDesc()) {
        list.append(d);
    }

    int size = list.size();
    for (int i = 0; i < size; ++i) {
        JObjectStreamClass *d = list.last();
        list.removeLast();
        if (d->getNumFields() > 0) {
            if (obj != NULL && d->hasReadObjectMethod()) {
                SerialCallbackContext oldContext = curContext;
                curContext.setContext(obj,d);
                bin->setBlockDataMode(true);
                //TODO handle exception
                ((JSerializable*)obj)->readObject(this);
                curContext = oldContext;

                /*
                 * defaultDataEnd may have been set indirectly by custom
                 * readObject() method when calling defaultReadObject() or
                 * readFields(); clear it to restore normal read behavior.
                 */
                defaultDataEnd = false;
            }
            else {
                defaultReadFields(obj,d);
            }
            if (d->hasWriteObjectData()) {
                skipCustomData();
            }
            else {
                bin->setBlockDataMode(false);
            }
        }
    }
}

void JObjectInputStream::defaultReadFields(JObject *obj, JObjectStreamClass *desc) {
    int primDataSize = desc->getPrimDataSize();
    delete[] primVals; // make sure it is NULL or has been previously allocated with new
    primVals = new qint8[primDataSize];
    bin->readFully(primVals,0,primDataSize,false);
    if (obj != NULL) {
        desc->setPrimFieldValues(obj, primVals);
    }

    int objHandle = passHandle;
    int numObjFields = desc->getNumObjFields();
    JObject **objVals = new JObject*[numObjFields];
    for (int i = 0; i < numObjFields; ++i) {
        JObject* readObj = readObject0();
        objVals[i] = readObj;
    }
    if (obj != NULL) {
        desc->setObjectFieldValues(obj,objVals);
    }
    delete[] objVals;
    passHandle = objHandle;
}

/**
 * Skips over all block data and objects until TC_ENDBLOCKDATA is
 * encountered.
 */
void JObjectInputStream::skipCustomData() {
    int oldHandle = passHandle;
    for (;;) {
        if (bin->getBlockDataMode()) {
            bin->skipBlockData();
            bin->setBlockDataMode(false);
        }
        switch (bin->peekByte()) {
        case TC_BLOCKDATA:
        case TC_BLOCKDATALONG:
            bin->setBlockDataMode(true);
            break;

        case TC_ENDBLOCKDATA:
            bin->readByte();
            passHandle = oldHandle;
            return;

        default:
            readObject0();
            break;
        }
    }
}

int JObjectInputStream::read() {
    return bin->read();
}

int JObjectInputStream::read(qint8 b[], int off, int len) {
    return bin->read(b,off,len);
}

qint8 JObjectInputStream::readByte() {
    return bin->readByte();
}

/**
 * reads Java char type, which is on 2 bytes
 */
char JObjectInputStream::readChar() {
    return bin->readChar();
}

double JObjectInputStream::readDouble() {
    return bin->readDouble();
}

float JObjectInputStream::readFloat() {
    return bin->readFloat();
}

qint32 JObjectInputStream::readInt() {
    return bin->readInt();
}

qint64 JObjectInputStream::readLong() {
    return bin->readLong();
}

qint16 JObjectInputStream::readShort() {
    return bin->readShort();
}

bool JObjectInputStream::readBool() {
    return bin->readBool();
}

string JObjectInputStream::readUTF() {
    return bin->readUTF();
}

string JObjectInputStream::readLongUTF() {
    return bin->readLongUTF();
}

JString* JObjectInputStream::readString() {
    qint8 tc = bin->readByte();
    string str;
    switch (tc) {
    case TC_STRING:
        str = bin->readUTF();
        break;

    case TC_LONGSTRING:
        str = bin->readLongUTF();
        break;

    default:
        stringstream ss;
        ss<<"invalid type code: "<<tc;
        throw new JStreamCorruptedException(ss.str());
    }
    JString* mstr = new JString(str);
    passHandle = handles->assign((JObject*) mstr);
    handles->finish(passHandle);
    return mstr;
}

/**
 * Clears internal data structures.
 */
void JObjectInputStream::clear() {
    handles->clear();
}

JClass *JObjectInputStream::resolveClass(JObjectStreamClass* desc) {
    return (classLoader->loadClass(desc->getName()));
}

JClass *JObjectInputStream::resolveProxyClass(string *ifaces, int numIfaces) {
    string proxySignature = "";
    for (int i = 0; i < numIfaces; ++i) {
        proxySignature += ifaces[i];
    }
    return classLoader->loadClass(proxySignature);//TODO create Proxy class that contain all the passed interfaces
}

void JObjectInputStream::close(){
    this->bin->close();
}
