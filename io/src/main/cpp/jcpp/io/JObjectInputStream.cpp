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
#include "JClassCastException.h"
#include "JPrimitiveShort.h"
#include <cstdio>
#include <sstream>
#include "JExternalizable.h"
#include "Object.h"

using namespace std;

namespace jcpp{
    namespace io{
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

        JObjectInputStream::JObjectInputStream(JInputStream *in,JClass* _class):JInputStream(_class){
            inputClassLoader=JClassLoader::getBootClassLoader();
            bin = new BlockDataInputStream(in);
            passHandle = NULL_HANDLE;
            handles = new HandleTable(100);
            primVals = NULL;
            defaultDataEnd  = false;

            // check stream header
            jshort s0 = readShort();
            jshort s1 = readShort();
            if (s0 != STREAM_MAGIC || s1 != STREAM_VERSION) {
                stringstream ss;
                ss<<"invalid stream header "<<s0<<","<<s1;
                throw new JStreamCorruptedException(ss.str());
            }
            bin->setBlockDataMode(true);
        }

        JObjectInputStream::JObjectInputStream(JInputStream *in):JInputStream(getClazz()){
            inputClassLoader=JClassLoader::getBootClassLoader();
            bin = new BlockDataInputStream(in);
            passHandle = NULL_HANDLE;
            handles = new HandleTable(100);
            primVals = NULL;
            defaultDataEnd  = false;

            // check stream header
            jshort s0 = readShort();
            jshort s1 = readShort();
            if (s0 != STREAM_MAGIC || s1 != STREAM_VERSION) {
                stringstream ss;
                ss<<"invalid stream header "<<s0<<","<<s1;
                throw new JStreamCorruptedException(ss.str());
            }
            bin->setBlockDataMode(true);
        }

        void JObjectInputStream::setInputClassLoader(JClassLoader* inputClassLoader){
            this->inputClassLoader=inputClassLoader;
        }

        JObjectInputStream::~JObjectInputStream() {
            delete handles;
            delete bin;
        }

        jlong JObjectInputStream::available() {
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
            int outerHandle=passHandle;
            JObject* obj=readObject0();
            handles->markDependency(outerHandle,passHandle);
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            if (ex!=NULL){
                throw ex;
            }
            passHandle=outerHandle;
            return obj;
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

            jbyte tc;
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

            case TC_CLASS:
                obj=readClass();
                break;

            case TC_CLASSDESC:
            case TC_PROXYCLASSDESC:
                obj=readClassDesc();
                break;

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

            case TC_EXCEPTION:{
                    JIOException* ex1 = readFatalException();
                    throw ex1;
                }
                break;

            case TC_BLOCKDATA:
            case TC_BLOCKDATALONG:
                if (oldMode){
                    bin->setBlockDataMode(true);
                    bin->peek();
                    stringstream ss;
                    ss<<"remaining data block "<<bin->currentBlockRemaining();
                    throw new JOptionalDataException(ss.str());
                }else{
                    throw new JStreamCorruptedException("unexpected block data");
                }

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
            if (!enableResolve || handles->lookupException(passHandle)) {
                return obj;
            }
            JObject* rep = resolveObject(obj);
            if (rep != obj) {
                handles->setObject(passHandle, rep);
            }
            return rep;
        }

        JString* JObjectInputStream::readTypeString() {
            JString* jstring=NULL;
            int oldHandle=passHandle;
            jbyte tc = bin->peekByte();
            switch (tc) {
            case TC_STRING:
            case TC_LONGSTRING:
                jstring=readString();
                break;

            case TC_NULL:
                jstring=(JString*) (readNull());
                break;

            case TC_REFERENCE:
                jstring=(JString*) (readHandle());
                break;

            default:
                passHandle=oldHandle;
                stringstream ss;
                ss<<"stream corrupted: invalid typecode "<<tc;
                throw new JStreamCorruptedException(ss.str());
            }
            passHandle=oldHandle;
            return jstring;
        }

        void JObjectInputStream::defaultReadObject() {
            if (!curContext->isUpcall()) {
                throw new JNotActiveException("not in call to readObject");
            }
            JObject* curObj = curContext->getObj();
            JObjectStreamClass* curDesc = curContext->getDesc();
            bin->setBlockDataMode(false);
            defaultReadFields(curObj, curDesc);
            bin->setBlockDataMode(true);
            if (!curDesc->hasWriteObjectData()) {
                defaultDataEnd = true;
            }
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            if (ex!=NULL){
                throw ex;
            }
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

        JObject* JObjectInputStream::readClass(){
            if (bin->readByte() != TC_CLASS){
                throw new JInternalError();
            }
            JObjectStreamClass* desc=readClassDesc();
            JClass* jClass=desc->getJClass();
            passHandle=handles->assign(jClass);

            JClassNotFoundException* resolveEx = desc->getResolveException();
            if (resolveEx!=NULL){
                handles->markException(passHandle,resolveEx);
            }

            handles->finish(passHandle);
            return jClass;
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
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=NULL){
                handles->markException(arrayHandle,resolveEx);
            }

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
                    handles->markDependency(arrayHandle,passHandle);
                }
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
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=NULL){
                handles->markException(enumHandle,resolveEx);
            }

            JString* mname = readString();
            string name = mname->getString();
            JEnum* en = desc->getJClass()->valueOf(name);
            handles->setObject(enumHandle,en);
            handles->finish(enumHandle);
            passHandle = enumHandle;
            return en;
        }

        JObjectStreamClass* JObjectInputStream::readClassDesc() {
            jbyte tc = bin->peekByte();

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
            jint descHandle = handles->assign(desc);
            passHandle = NULL_HANDLE;

            int numIfaces = bin->readInt();
            string *ifaces = new string[numIfaces];
            for (int i = 0; i < numIfaces; ++i) {
                ifaces[i] = bin->readUTF();
            }

            JClass* metaObj=NULL;
            JClassNotFoundException* resolveEx=NULL;
            bin->setBlockDataMode(true);
            try{
                metaObj = resolveProxyClass(ifaces,numIfaces);
                if(metaObj==NULL){
                    resolveEx=new JClassNotFoundException("null class");
                }
            }catch(JClassNotFoundException* ex){
                resolveEx=ex;
            }
            skipCustomData();

            desc->initProxy(metaObj, resolveEx,readClassDesc());

            handles->finish(descHandle);
            passHandle = descHandle;

            delete ifaces;

            return desc;
        }

        JObjectStreamClass* JObjectInputStream::readNonProxyDesc() {
            if (bin->readByte() != TC_CLASSDESC) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = new JObjectStreamClass;
            jint descHandle = handles->assign(desc);
            passHandle = NULL_HANDLE;

            JObjectStreamClass *readDesc = new JObjectStreamClass;
            readDesc->readNonProxy(this);

            JClass* metaObj=NULL;
            JClassNotFoundException* resolveEx=NULL;
            bin->setBlockDataMode(true);
            try{
                metaObj = resolveClass(readDesc);
                if (metaObj==NULL){
                    resolveEx=new JClassNotFoundException("null class");
                }
            }catch(JClassNotFoundException* ex){
                resolveEx=ex;
            }
            skipCustomData();

            desc->initNonProxy(readDesc, metaObj, resolveEx,readClassDesc());

            handles->finish(descHandle);
            passHandle = descHandle;

            delete readDesc;

            return desc;
        }

        JObject* JObjectInputStream::readOrdinaryObject() {
            if (bin->readByte() != TC_OBJECT) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = readClassDesc();

            JObject* obj = desc->newInstance();
            passHandle = handles->assign(obj);
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=NULL){
                handles->markException(passHandle,resolveEx);
            }

            if (desc->isExternalizable()){
                readExternalData(obj,desc);
            }else{
                readSerialData(obj, desc);
            }

            handles->finish(passHandle);
            return obj;
        }

        void JObjectInputStream::readExternalData(JObject* obj, JObjectStreamClass* desc){
            SerialCallbackContext* oldContext=curContext;
            curContext=NULL;
            bool blocked=desc->hasBlockExternalData();
            if (blocked){
                bin->setBlockDataMode(true);
            }
            if (obj!=NULL){
                ((JExternalizable*)obj)->readExternal(this);
            }
            if (blocked){
                skipCustomData();
            }
            curContext=oldContext;
        }

        void JObjectInputStream::readSerialData(JObject *obj, JObjectStreamClass *desc) {
            vector<JObjectStreamClass::ClassDataSlot*>* dataSlots=desc->getClassDataLayout();
            for (unsigned int i=0;i<dataSlots->size();i++){
                JObjectStreamClass::ClassDataSlot* dataSlot=dataSlots->at(i);
                JObjectStreamClass* slotDesc=dataSlot->desc;
                if (obj!=NULL && slotDesc->hasReadObjectMethod() && handles->lookupException(passHandle)==NULL){
                    SerialCallbackContext* oldContext = curContext;
                    try{
                        curContext=new SerialCallbackContext();
                        curContext->setContext(obj,slotDesc);
                        bin->setBlockDataMode(true);
                        slotDesc->invokeReadObject(obj,this);
                    }catch(JClassNotFoundException* ex){
                        handles->markException(passHandle,ex);
                    }
                    delete curContext;
                    curContext=oldContext;

                    defaultDataEnd = false;

                }else {
                    defaultReadFields(obj,slotDesc);
                }
                if (slotDesc->hasWriteObjectData()) {
                    skipCustomData();
                }else {
                    bin->setBlockDataMode(false);
                }
            }
        }

        void JObjectInputStream::defaultReadFields(JObject *obj, JObjectStreamClass *desc) {
            JClass* cl=desc->getJClass();
            if (cl!=NULL && obj!=NULL && !cl->isInstance(obj)){
                throw new JClassCastException("object "+obj->toString()+" of class "+obj->getClass()->toString()+" is not instance of "+cl->toString());
            }

            int primDataSize = desc->getPrimDataSize();
            delete[] primVals; // make sure it is NULL or has been previously allocated with new
            primVals = new jbyte[primDataSize];
            bin->readFully(primVals,0,primDataSize,false);
            if (obj != NULL) {
                desc->setPrimFieldValues(obj, primVals);
            }

            int objHandle = passHandle;
            int numObjFields = desc->getNumObjFields();
            JObject **objVals = new JObject*[numObjFields];
            int numPrimFields=desc->getNumFields()-desc->getNumObjFields();
            for (int i = 0; i < numObjFields; ++i) {
                JObjectStreamField* f=desc->getField(numPrimFields+i);
                JObject* readObj = readObject0();
                objVals[i] = readObj;
                if (f->getField()!=NULL){
                    handles->markDependency(objHandle,passHandle);
                }
            }
            if (obj != NULL) {
                desc->setObjectFieldValues(obj,objVals);
            }
            delete[] objVals;
            passHandle = objHandle;
        }

        JIOException* JObjectInputStream::readFatalException(){
            if (bin->readByte()!=TC_EXCEPTION){
                throw new JInternalError();
            }
            clear();
            return (JIOException*)readObject0();
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

        jbyte JObjectInputStream::read() {
            return bin->read();
        }

        int JObjectInputStream::read(jbyte b[], int off, int len) {
            return bin->read(b,off,len);
        }

        jbyte JObjectInputStream::readByte() {
            return bin->readByte();
        }

        /**
         * reads Java char type, which is on 2 bytes
         */
        jchar JObjectInputStream::readChar() {
            return bin->readChar();
        }

        jdouble JObjectInputStream::readDouble() {
            return bin->readDouble();
        }

        jfloat JObjectInputStream::readFloat() {
            return bin->readFloat();
        }

        jint JObjectInputStream::readInt() {
            return bin->readInt();
        }

        jlong JObjectInputStream::readLong() {
            return bin->readLong();
        }

        jshort JObjectInputStream::readShort() {
            return bin->readShort();
        }

        jbool JObjectInputStream::readBool() {
            return bin->readBool();
        }

        JPrimitiveByte* JObjectInputStream::readPrimitiveByte(){
            return new JPrimitiveByte(readByte());
        }

        JPrimitiveChar* JObjectInputStream::readPrimitiveChar(){
            return new JPrimitiveChar(readChar());
        }

        JPrimitiveDouble* JObjectInputStream::readPrimitiveDouble(){
            return new JPrimitiveDouble(readDouble());
        }

        JPrimitiveFloat* JObjectInputStream::readPrimitiveFloat(){
            return new JPrimitiveFloat(readFloat());
        }

        JPrimitiveInt* JObjectInputStream::readPrimitiveInt(){
            return new JPrimitiveInt(readInt());
        }

        JPrimitiveLong* JObjectInputStream::readPrimitiveLong(){
            return new JPrimitiveLong(readLong());
        }

        JPrimitiveShort* JObjectInputStream::readPrimitiveShort(){
            return new JPrimitiveShort(readLong());
        }

        JPrimitiveBoolean* JObjectInputStream::readPrimitiveBool(){
            return new JPrimitiveBoolean(readBool());
        }

        string JObjectInputStream::readUTF() {
            return bin->readUTF();
        }

        string JObjectInputStream::readLongUTF() {
            return bin->readLongUTF();
        }

        JString* JObjectInputStream::readString() {
            jbyte tc = bin->readByte();
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
            return (inputClassLoader->loadClass(desc->getName()));
        }

        JClass *JObjectInputStream::resolveProxyClass(string *ifaces, int numIfaces) {
            string proxySignature = "";
            for (int i = 0; i < numIfaces; ++i) {
                proxySignature += ifaces[i];
            }
            return inputClassLoader->loadClass(proxySignature);//TODO create Proxy class that contain all the passed interfaces
        }

        void JObjectInputStream::close(){
            this->bin->close();
        }
    }
}
