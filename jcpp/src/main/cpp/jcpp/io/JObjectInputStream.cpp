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
#include "JProxy.h"
#include "JBlockDataInputStream.h"
#include "JInvalidObjectException.h"

using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{
        class JObjectInputStreamClass : public JClass{
        public:
            JObjectInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectInputStream";
                name="java.io.ObjectInputStream";
                simpleName="ObjectInputStream";
                addInterface(JObjectStreamConstants::getClazz());
                addInterface(JObjectInput::getClazz());
            }

            JClass* getSuperclass(){
                return JInputStream::getClazz();
            }

            virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JObjectInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectInputStreamClass();
            }
            return clazz;
        }

        class JGetFieldClass : public JClass{
        public:
            JGetFieldClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectInputStream$GetField";
                name="java.io.ObjectInputStream$GetField";
                simpleName="ObjectInputStream$GetField";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual JClass* getDeclaringClass(){
                return JObjectInputStream::getClazz();
            }
        };

        static JClass* getFieldClazz;
        JClass* JObjectInputStream::JGetField::getClazz(){
            if (getFieldClazz==NULL){
                getFieldClazz=new JGetFieldClass();
            }
            return getFieldClazz;
        }

        JObjectInputStream::JGetField::~JGetField(){
        }

        class JGetFieldImplClass : public JClass{
        public:
            JGetFieldImplClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectInputStream$GetFieldImpl";
                name="java.io.ObjectInputStream$GetFieldImpl";
                simpleName="ObjectInputStream$GetFieldImpl";
            }

            JClass* getSuperclass(){
                return JObjectInputStream::JGetField::getClazz();
            }

            virtual JClass* getDeclaringClass(){
                return JObjectInputStream::getClazz();
            }
        };

        static JClass* getFieldImplClazz;
        class JGetFieldImpl : public JObjectInputStream::JGetField{
        protected:
            JObjectInputStream* in;
            JObjectStreamClass* desc;
            jbyte* primVals;
            JObject** objVals;
            jint* objHandles;

        public:
            JGetFieldImpl(JObjectInputStream* in,JObjectStreamClass* desc):JGetField(getClazz()){
                this->in=in;
                this->desc=desc;
                primVals=new jbyte[desc->getPrimDataSize()];
                objVals=new JObject*[desc->getNumObjFields()];
                objHandles=new jint[desc->getNumObjFields()];
            }

            static JClass* getClazz(){
                if (getFieldImplClazz==NULL){
                    getFieldImplClazz=new JGetFieldImplClass();
                }
                return getFieldImplClazz;
            }

            JObjectStreamClass* getObjectStreamClass(){
                return desc;
            }

            virtual jbool defaulted(string name){
                return (getFieldOffset(name, NULL) < 0);
            }

            virtual jbool get(string name, jbool val){
                jint off = getFieldOffset(name, JBoolean::TYPE);
                return ((off >= 0) ? JBits::getBool(primVals, off) : val);
            }

            virtual jbyte get(string name, jbyte val){
                jint off = getFieldOffset(name, JByte::TYPE);
                return (off >= 0) ? primVals[off] : val;
            }

            virtual jchar get(string name, jchar val){
                jint off = getFieldOffset(name, JChar::TYPE);
                return (off >= 0) ? JBits::getChar(primVals, off) : val;
            }

            virtual jshort get(string name, jshort val){
                jint off = getFieldOffset(name, JShort::TYPE);
                return (off >= 0) ? JBits::getShort(primVals, off) : val;
            }

            virtual jint get(string name, jint val){
                jint off = getFieldOffset(name, JInteger::TYPE);
                return (off >= 0) ? JBits::getInt(primVals, off) : val;
            }

            virtual jfloat get(string name, jfloat val){
                jint off = getFieldOffset(name, JFloat::TYPE);
                return (off >= 0) ? JBits::getFloat(primVals, off) : val;
            }

            virtual jlong get(string name, jlong val){
                jint off = getFieldOffset(name, JLong::TYPE);
                return (off >= 0) ? JBits::getLong(primVals, off) : val;
            }

            virtual jdouble get(string name, jdouble val){
                jint off = getFieldOffset(name, JDouble::TYPE);
                return (off >= 0) ? JBits::getDouble(primVals, off) : val;
            }

            virtual JObject* get(string name, JObject* val){
                jint off = getFieldOffset(name, JObject::getClazz());
                if (off >= 0) {
                    jint objHandle = objHandles[off];
                    in->handles->markDependency(in->passHandle, objHandle);
                    return ((in->handles->lookupException(objHandle) == NULL) ? objVals[off] : NULL);
                } else {
                    return val;
                }
            }

            void readFields(){
                in->bin->readFully(primVals, 0, desc->getPrimDataSize(), false);
                jint oldHandle = in->passHandle;
                vector<JObjectStreamField*>* fields = desc->getFields();
                jint numPrimFields = fields->size()- desc->getNumObjFields();
                for (jint i = 0; i < desc->getNumObjFields(); i++) {
                    JObjectStreamField* f=fields->at(numPrimFields + i);
                    objVals[i] = in->readObject0(f->isUnshared());
                    objHandles[i] = in->passHandle;
                }
                in->passHandle = oldHandle;
            }

            jint getFieldOffset(string name, JClass* type) {
                JObjectStreamField* field = desc->getField(name, type);
                if (field != NULL) {
                    return field->getOffset();
                } else if (desc->getLocalDesc()->getField(name, type) != NULL) {
                    return -1;
                } else {
                    throw new JIllegalArgumentException("no such field " + name +" with type " + type->toString());
                }
            }

            ~JGetFieldImpl(){
                delete[] primVals;
                delete[] objVals;
                delete[] objHandles;
            }
        };

        void JObjectInputStreamClass::fillDeclaredClasses(){
            addDeclaredClass(JBlockDataInputStream::getClazz());
            addDeclaredClass(JObjectInputStream::JGetField::getClazz());
            addDeclaredClass(JGetFieldImpl::getClazz());
        }

        static JObject* unsharedMarker = new JObject();

        JObjectInputStream::JObjectInputStream(JInputStream *in,JClass* _class):JInputStream(_class){
            init(in);
        }

        JObjectInputStream::JObjectInputStream(JInputStream *in):JInputStream(getClazz()){
            init(in);
        }

        void JObjectInputStream::init(JInputStream* in){
            inputClassLoader=JClassLoader::getBootClassLoader();
            bin = new JBlockDataInputStream(in);
            passHandle = NULL_HANDLE;
            handles = new HandleTable(100);
            primVals = NULL;
            curContext=NULL;
            enableResolve=false;

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
            if (primVals!=NULL){
                delete[] primVals;
            }
            if (curContext!=NULL){
                delete curContext;
            }
        }

        jint JObjectInputStream::available() {
            return bin->available();
        }

        jbool JObjectInputStream::enableResolveObject(jbool enable) {
            if (enable == enableResolve) {
                return enable;
            }
            enableResolve = enable;
            return !enableResolve;
        }

        void JObjectInputStream::readFully(jbyte b[], jint off, jint len){
            bin->readFully(b,off,len,false);
        }

        jint JObjectInputStream::skipBytes(jint n){
            return bin->skipBytes(n);
        }

        jlong JObjectInputStream::skip(jlong n){
            return bin->skip(n);
        }

        jint JObjectInputStream::readUnsignedByte(){
            return bin->readUnsignedByte();
        }

        jint JObjectInputStream::readUnsignedShort(){
            return bin->readUnsignedShort();
        }

        JObject* JObjectInputStream::readObject() {
            jint outerHandle=passHandle;
            JObject* obj=readObject0(false);
            handles->markDependency(outerHandle,passHandle);
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            if (ex!=NULL){
                throw ex;
            }
            passHandle=outerHandle;
            return obj;
        }

        JObject* JObjectInputStream::readObject0(jbool unshared) {
            jbool oldMode = bin->getBlockDataMode();
            if (oldMode) {
                jint remain = bin->currentBlockRemaining();
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
                obj = readHandle(unshared);
                break;

            case TC_CLASS:
                obj=readClass(unshared);
                break;

            case TC_CLASSDESC:
            case TC_PROXYCLASSDESC:
                obj=readClassDesc(unshared);
                break;

            case TC_STRING:
            case TC_LONGSTRING:
                obj = checkResolve(readString(unshared));
                break;

            case TC_ARRAY:
                obj = checkResolve(readArray(unshared));
                break;

            case TC_ENUM:
                obj = checkResolve(readEnum(unshared));
                break;

            case TC_OBJECT:
                obj = checkResolve(readOrdinaryObject(unshared));
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
            if (!enableResolve || handles->lookupException(passHandle)!=NULL) {
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
            jint oldHandle=passHandle;
            jbyte tc = bin->peekByte();
            switch (tc) {
                case TC_STRING:
                case TC_LONGSTRING:
                    jstring=readString(false);
                    break;

                case TC_NULL:
                    jstring=(JString*) (readNull());
                    break;

                case TC_REFERENCE:
                    jstring=(JString*) (readHandle(false));
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

        JObject* JObjectInputStream::readUnshared(){
            jint outerHandle=passHandle;
            JObject* obj=readObject0(true);
            handles->markDependency(outerHandle,passHandle);
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            passHandle=outerHandle;
            if (ex!=NULL){
                throw ex;
            }
            return obj;
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
                bin->setDefaultDataEnd(true);
            }
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            if (ex!=NULL){
                throw ex;
            }
        }

        JObjectInputStream::JGetField* JObjectInputStream::readFields(){
            if (curContext == NULL) {
                throw new JNotActiveException("not in call to readObject");
            }
            curContext->getObj();
            JObjectStreamClass* curDesc = curContext->getDesc();
            bin->setBlockDataMode(false);
            JGetFieldImpl* getField = new JGetFieldImpl(this,curDesc);
            getField->readFields();
            bin->setBlockDataMode(true);
            return getField;
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

        JObject* JObjectInputStream::readHandle(jbool unshared) {
            if (bin->readByte() != TC_REFERENCE) {
                throw new JInternalError();
            }
            passHandle = bin->readInt() - baseWireHandle;
            if (passHandle < 0 || passHandle >= handles->getSize()) {
                throw new JStreamCorruptedException("invalid handle value");
            }
            if (unshared){
                throw new JInvalidObjectException("cannot read back reference as unshared");
            }
            JObject* obj = handles->lookupObject(passHandle);
            if (obj==unsharedMarker){
                throw new JInvalidObjectException("cannot read back reference as unshared");
            }
            return obj;
        }

        JObject* JObjectInputStream::readClass(jbool unshared){
            if (bin->readByte() != TC_CLASS){
                throw new JInternalError();
            }
            JObjectStreamClass* desc=readClassDesc(false);
            JClass* jClass=desc->getJClass();
            passHandle=handles->assign((unshared ? unsharedMarker : jClass));

            JClassNotFoundException* resolveEx = desc->getResolveException();
            if (resolveEx!=NULL){
                handles->markException(passHandle,resolveEx);
            }

            handles->finish(passHandle);
            return jClass;
        }

        JObject* JObjectInputStream::readArray(jbool unshared){
            if (bin->readByte() != TC_ARRAY) {
                throw new JInternalError();
            }

            JObjectStreamClass* desc = readClassDesc(false);
            jint len = bin->readInt();

            JPrimitiveArray* pArray = NULL;
            JClass* cl=desc->getJClass();
            JClass* ccl=NULL;
            if (cl != NULL) {
                ccl = cl->getComponentType();
                pArray = new JPrimitiveArray(ccl,len);
            }

            jint arrayHandle = handles->assign((unshared ? unsharedMarker : pArray));
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=NULL){
                handles->markException(arrayHandle,resolveEx);
            }

            if(ccl==NULL) {
                for (jint i = 0; i < len; i++) {
                    readObject0(false);
                }
            }else if (ccl->isPrimitive()){
                if (ccl == JPrimitiveByte::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveByte(readByte()));
                    }

                }else if (ccl==JPrimitiveChar::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveChar(readChar()));
                    }

                }else if (ccl==JPrimitiveDouble::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveDouble(readDouble()));
                    }

                }else if (ccl==JPrimitiveFloat::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveFloat(readFloat()));
                    }

                }else if (ccl == JPrimitiveInt::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveInt(readInt()));
                    }

                }else if (ccl==JPrimitiveLong::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveLong(readLong()));
                    }

                }else if (ccl==JPrimitiveShort::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveShort(readShort()));
                    }

                }else if (ccl==JPrimitiveBoolean::getClazz()) {
                    for (jint i = 0; i < len; ++i) {
                        pArray->set(i,new JPrimitiveBoolean(readBool()));
                    }

                }else {
                    throw new JInternalError();
                }
            }else{
                for (jint i = 0 ; i < len; ++i) {
                    pArray->set(i,readObject0(false));
                    handles->markDependency(arrayHandle,passHandle);
                }
            }

            handles->finish(arrayHandle);
            passHandle = arrayHandle;
            return pArray;
        }

        JObject* JObjectInputStream::readEnum(jbool unshared) {
            if (bin->readByte() != TC_ENUM) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = readClassDesc(false);
            if (!desc->isEnum()){
                throw new JInvalidClassException("non-enum class: " + desc->toString());
            }

            jint enumHandle = handles->assign((unshared ? unsharedMarker : NULL));
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=NULL){
                handles->markException(enumHandle,resolveEx);
            }

            JString* mname = readString(false);
            string name = mname->getString();
            JEnum* en = desc->getJClass()->valueOf(name);
            if (!unshared){
                handles->setObject(enumHandle,en);
            }
            handles->finish(enumHandle);
            passHandle = enumHandle;
            return en;
        }

        JObjectStreamClass* JObjectInputStream::readClassDesc(jbool unshared) {
            jbyte tc = bin->peekByte();

            switch (tc) {
            case TC_NULL:
                return (JObjectStreamClass*) (readNull());

            case TC_REFERENCE:
                return (JObjectStreamClass*) (readHandle(unshared));

            case TC_CLASSDESC:
                return readNonProxyDesc(unshared);

            case TC_PROXYCLASSDESC:
                return readProxyDesc(unshared);

            default:
                stringstream ss;
                ss<<"invalid type code: "<<tc;
                throw new JStreamCorruptedException(ss.str());
            }
        }

        JObjectStreamClass* JObjectInputStream::readProxyDesc(jbool unshared) {
            if (bin->readByte() != TC_PROXYCLASSDESC) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = new JObjectStreamClass;
            jint descHandle = handles->assign((unshared ? unsharedMarker : desc));
            passHandle = NULL_HANDLE;

            jint numIfaces = bin->readInt();
            string *ifaces = new string[numIfaces];
            for (jint i = 0; i < numIfaces; ++i) {
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

            desc->initProxy(metaObj, resolveEx,readClassDesc(false));

            handles->finish(descHandle);
            passHandle = descHandle;

            delete ifaces;

            return desc;
        }

        JObjectStreamClass* JObjectInputStream::readNonProxyDesc(jbool unshared) {
            if (bin->readByte() != TC_CLASSDESC) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = new JObjectStreamClass;
            jint descHandle = handles->assign((unshared ? unsharedMarker : desc));
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

            desc->initNonProxy(readDesc, metaObj, resolveEx,readClassDesc(false));

            handles->finish(descHandle);
            passHandle = descHandle;

            delete readDesc;

            return desc;
        }

        JObject* JObjectInputStream::readOrdinaryObject(jbool unshared) {
            if (bin->readByte() != TC_OBJECT) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = readClassDesc(false);

            JObject* obj = desc->newInstance();
            passHandle = handles->assign((unshared ? unsharedMarker : obj));
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
            jbool blocked=desc->hasBlockExternalData();
            if (blocked){
                bin->setBlockDataMode(true);
            }
            if (obj!=NULL){
                (dynamic_cast<JExternalizable*>(obj))->readExternal(this);
            }
            if (blocked){
                skipCustomData();
            }
            curContext=oldContext;
        }

        void JObjectInputStream::readSerialData(JObject *obj, JObjectStreamClass *desc) {
            if (obj==NULL){
                return;
            }
            vector<JObjectStreamClass::ClassDataSlot*>* dataSlots=desc->getClassDataLayout();
            for (jint i=0;i<dataSlots->size();i++){
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

                    bin->setDefaultDataEnd(false);

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

            jint primDataSize = desc->getPrimDataSize();
            delete[] primVals;
            primVals = new jbyte[primDataSize];
            bin->readFully(primVals,0,primDataSize,false);
            if (obj != NULL) {
                desc->setPrimFieldValues(obj, primVals);
            }

            jint objHandle = passHandle;
            jint numObjFields = desc->getNumObjFields();
            JObject **objVals = new JObject*[numObjFields];
            jint numPrimFields=desc->getNumFields()-desc->getNumObjFields();
            for (jint i = 0; i < numObjFields; ++i) {
                JObjectStreamField* f=desc->getField(numPrimFields+i);
                JObject* readObj = readObject0(f->isUnshared());
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
            return (JIOException*)readObject0(false);
        }

        void JObjectInputStream::skipCustomData() {
            jint oldHandle = passHandle;
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
                        readObject0(false);
                        break;
                }
            }
        }

        jint JObjectInputStream::read() {
            return bin->read();
        }

        jint JObjectInputStream::read(jbyte b[], jint off, jint len) {
            return bin->read(b,off,len);
        }

        jbyte JObjectInputStream::readByte() {
            return bin->readByte();
        }

        jint JObjectInputStream::peek() {
            return bin->peek();
        }

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
            return new JPrimitiveShort(readShort());
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

        JString* JObjectInputStream::readString(jbool unshared) {
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
            passHandle = handles->assign((unshared ? unsharedMarker : (JObject*) mstr));
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

        JClass *JObjectInputStream::resolveProxyClass(string *ifaces, jint numIfaces) {
            vector<JClass*>* interfaces=new vector<JClass*>();
            for (jint i = 0; i < numIfaces; ++i) {
                JClass* c=inputClassLoader->loadClass(ifaces[i]);
                interfaces->push_back(c);
            }
            JClass* pc=JProxy::getProxyClass(interfaces);
            delete interfaces;
            return pc;
        }

        void JObjectInputStream::close(){
            this->bin->close();
        }
    }
}
