#include "JObjectOutputStream.h"

#include <iostream>
#include "JObjectOutputStream.h"
#include "BlockDataOutputStream.h"
#include "JClassLoader.h"
#include "JObject.h"
#include "JEnum.h"
#include "JIOException.h"
#include "JSerializable.h"
#include "JArrayList.h"
#include "JNotSerializableException.h"
#include "JLang.h"
#include "JExternalizable.h"

JObjectOutputStream::JObjectOutputStream(){
    handles = new OutputHandleTable();
}

JObjectOutputStream::JObjectOutputStream(JOutputStream* out){
    this->bout = new JBlockDataOutputStream(out);
    handles=new OutputHandleTable();
    enableOverride = false;
    enableReplaceObject(false);
    depth = 0;
    writeStreamHeader();
    bout->setBlockDataMode(true);
}

bool JObjectOutputStream::enableReplaceObject(bool enable) {
    if (enable == enableReplace) {
        return enable;
    }
    enableReplace = enable;
    return !enableReplace;
}

void JObjectOutputStream::writeBoolean(bool b){
    bout->writeBoolean(b);
}

void JObjectOutputStream::writeByte(qint8 b){
    bout->writeByte(b);
}

void JObjectOutputStream::writeChar(quint16 v){
    bout->writeChar(v);
}

void JObjectOutputStream::writeDouble(double v){
    bout->writeDouble(v);
}

void JObjectOutputStream::writeFloat(float v){
    bout->writeFloat(v);
}

void JObjectOutputStream::writeShort(qint16 v){
    bout->writeShort(v);
}

void JObjectOutputStream::writeInt(qint32 v){
    bout->writeInt(v);
}

void JObjectOutputStream::writeLong(qint64 v){
    bout->writeLong(v);
}

void JObjectOutputStream::writeObject(JObject *obj){
    if(enableOverride)
        writeObjectOverride(obj);
    else{
        try{
            writeObject0(obj);
        }catch(JIOException* e){
            if (depth == 0) {
                writeFatalException(e);
            }
            throw e;
        }
    }
}

void JObjectOutputStream::flush(){
    bout->flush();
}

void JObjectOutputStream::close(){
    bout->close();
}

void JObjectOutputStream::writeStreamHeader(){
    bout->writeShort(STREAM_MAGIC);
    bout->writeShort(STREAM_VERSION);
}

void JObjectOutputStream::writeObject0(JObject* obj){
    bool oldMode = bout->setBlockDataMode(false);
    depth++;
    if(obj == NULL){
        writeNull();
    }else{
        int handle;
        if( (handle = handles->lookup(obj) != -1) ){
            writeHandle(handle);
        }else if (JClass::getClazz()->isAssignableFrom(obj->getClass())){
            writeClass((JClass*)obj);
        }else if (JObjectStreamClass::getClazz()->isAssignableFrom(obj->getClass())){
            writeClassDesc((JObjectStreamClass*)obj);
        }else{
            JObjectStreamClass* desc = JObjectStreamClass::lookup(obj->getClass());
            curContext = new SerialCallbackContext();
            curContext->setContext(obj,desc);
            if (obj->getClazz()==JString::getClazz()){
                writeString((JString*)obj);

            }else if(obj->getClass()->isArray()){
                writeArray(obj,desc);

            } else if (obj->getClass()->isEnum()){
                 writeEnum(obj, desc);

            }else if (JSerializable::getClazz()->isAssignableFrom(obj->getClass())){
                writeOrdinaryObject(obj,desc);
            }else{
                throw new JNotSerializableException(obj->getClass()->getName());
            }
        }
    }
    depth--;
    bout->setBlockDataMode(oldMode);
}

JObject *JObjectOutputStream::replaceObject(JObject *obj) {
    return obj;
}

void JObjectOutputStream::writeOrdinaryObject(JObject* obj, JObjectStreamClass* desc){
    writeByte(TC_OBJECT);
    writeClassDesc(desc);
    handles->assign(obj);

    if (desc->isExternalizable() && !desc->isProxy()){
        writeExternalData(obj);
    }else{
        writeSerialData(obj,desc);
    }
}

void JObjectOutputStream::writeClass(JClass* cl){
    bout->writeByte(TC_CLASS);
    writeClassDesc(JObjectStreamClass::lookup(cl));
    handles->assign(cl);
}

void JObjectOutputStream::writeClassDesc(JObjectStreamClass* desc){
    qint32 handle;
    if(desc == NULL){
        writeNull();
    } else if( (handle = handles->lookup(desc)) != -1) {
        writeHandle(handle);
    } else if(desc->isProxy()){
        writeProxyDesc(desc);
    } else{
        writeNonProxyDesc(desc);
    }
}

void JObjectOutputStream::writeProxyDesc(JObjectStreamClass *desc){
    bout->writeByte(TC_PROXYCLASSDESC);
    handles->assign(desc);

    JClass* cl=desc->getJClass();
    vector<JClass*>* interfaces=cl->getInterfaces();
    bout->writeInt(interfaces->size());
    for(unsigned int i = 0; i < interfaces->size(); ++i){
        JClass* clazz=interfaces->at(i);
        bout->writeUTF(clazz->getName());
    }

    bout->setBlockDataMode(true);
    bout->setBlockDataMode(false);
    bout->writeByte(TC_ENDBLOCKDATA);
    writeClassDesc(desc->getSuperDesc());
}

void JObjectOutputStream::writeHandle(qint32 handle){
    bout->writeByte(TC_REFERENCE);
    bout->writeInt(baseWireHandle + handle);
}

void JObjectOutputStream::writeEnum(JObject *obj, JObjectStreamClass* desc){
    bout->writeByte(TC_ENUM);
    JObjectStreamClass* sdesc=desc->getSuperDesc();
    writeClassDesc((sdesc->getJClass()==JEnum::getClazz()?desc:sdesc));
    handles->assign(obj);
    writeString( ((JEnum*)obj)->getName());
}

void JObjectOutputStream::writeNonProxyDesc(JObjectStreamClass* desc){
    bout->writeByte(TC_CLASSDESC);
    handles->assign(desc);
    writeClassDescriptor(desc);
    bout->setBlockDataMode(true);
    bout->setBlockDataMode(false);
    bout->writeByte(TC_ENDBLOCKDATA);
    writeClassDesc(desc->getSuperDesc());
}

void JObjectOutputStream::writeExternalData(JObject* obj){
    SerialCallbackContext* oldContext=curContext;
    curContext=NULL;
    bout->setBlockDataMode(true);
    ((JExternalizable*)obj)->writeExternal(this);
    bout->setBlockDataMode(false);
    bout->writeByte(TC_ENDBLOCKDATA);
    curContext=oldContext;
}

void JObjectOutputStream::writeSerialData(JObject *obj, JObjectStreamClass* desc){
    vector<JObjectStreamClass::ClassDataSlot*>* classDataSlots=desc->getClassDataLayout();
    for (int i=0;i<classDataSlots->size();i++){
        JObjectStreamClass::ClassDataSlot* dataSlot=classDataSlots->at(i);
        JObjectStreamClass* slotDesc=dataSlot->desc;
        if (slotDesc->hasWriteObjectMethod()) {
            SerialCallbackContext* oldContext = curContext;
            curContext = new SerialCallbackContext();
            curContext->setContext(obj, slotDesc);
            bout->setBlockDataMode(true);
            slotDesc->invokeWriteObject(obj, this);
            bout->setBlockDataMode(false);
            bout->writeByte(TC_ENDBLOCKDATA);
            delete curContext;
            curContext = oldContext;
        } else {
            defaultWriteFields(obj, slotDesc);
        }
    }
}

void JObjectOutputStream::defaultWriteObject(){
    JObject* curObj = curContext->getObj();
    JObjectStreamClass* curDesc = curContext->getDesc();

    bout->setBlockDataMode(false);
    defaultWriteFields(curObj, curDesc);
    bout->setBlockDataMode(true);
}

void JObjectOutputStream::writeArray(JObject *obj, JObjectStreamClass* desc){
    bout->writeByte(TC_ARRAY);
    writeClassDesc(desc);
    handles->assign(obj);

    writeArrayProperties(obj);
}

void JObjectOutputStream::writeArrayProperties(JObject* array){
    JPrimitiveArray* primitiveArray=(JPrimitiveArray*)array;
    JClass* ccl=array->getClass()->getComponentType();
    bout->writeInt(primitiveArray->size());
    if (ccl->isPrimitive()){
        if (ccl==JPrimitiveInt::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveInt* jint=(JPrimitiveInt*)primitiveArray->get(i);
                bout->writeInt(jint->get());
            }
        }else if (ccl==JPrimitiveByte::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveByte* jbyte=(JPrimitiveByte*)primitiveArray->get(i);
                bout->writeByte(jbyte->get());
            }
        }else if (ccl==JPrimitiveLong::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveLong* jlong=(JPrimitiveLong*)primitiveArray->get(i);
                bout->writeLong(jlong->get());
            }
        }else if (ccl==JPrimitiveFloat::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveFloat* jfloat=(JPrimitiveFloat*)primitiveArray->get(i);
                bout->writeFloat(jfloat->get());
            }
        }else if (ccl==JPrimitiveDouble::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveDouble* jdouble=(JPrimitiveDouble*)primitiveArray->get(i);
                bout->writeDouble(jdouble->get());
            }
        }else if (ccl==JPrimitiveShort::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveShort* jshort=(JPrimitiveShort*)primitiveArray->get(i);
                bout->writeShort(jshort->get());
            }
        }else if (ccl==JPrimitiveChar::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveChar* jchar=(JPrimitiveChar*)primitiveArray->get(i);
                bout->writeChar(jchar->get());
            }
        }else if (ccl==JPrimitiveBoolean::getClazz()){
            for (int i=0;i<primitiveArray->size();i++){
                JPrimitiveBoolean* jbool=(JPrimitiveBoolean*)primitiveArray->get(i);
                bout->writeBoolean(jbool->get());
            }
        }else{
            throw new JInternalError();
        }
    }else{
        for (int i=0;i<primitiveArray->size();i++){
            writeObject0(primitiveArray->get(i));
        }
    }
}

void JObjectOutputStream::defaultWriteFields(JObject *obj, JObjectStreamClass* desc){
    int primDataSize = desc->getPrimDataSize();
    delete primVals;
    primVals = new qint8[primDataSize];
    desc->writePrimFieldValues(obj, primVals,this);
    bout->write(primVals, 0, primDataSize, false);

    if (desc->getNumObjFields() > 0){
        writeObjectValues(obj, desc);
    }
}

void JObjectOutputStream::writeFatalException(JIOException* ex){
    bool oldMode=bout->setBlockDataMode(false);
    bout->writeByte(TC_EXCEPTION);
    writeObject0(ex);
    bout->setBlockDataMode(oldMode);
}

void JObjectOutputStream::writePrimitiveData(JObject *obj, JObjectStreamClass *desc){
    int primDataSize = desc->getPrimDataSize();
    if (primVals == NULL || sizeof(primVals) < primDataSize) {
        primVals = new qint8[primDataSize];
    }
    desc->writePrimFieldValues(obj, primVals,this);
    bout->write(primVals, 0, primDataSize, false);
}

void JObjectOutputStream::writeObjectValues(JObject *obj, JObjectStreamClass *desc){
    for(int i = 0; i < desc->getNumFields(); i++){
        JObjectStreamField* osf = desc->getField(i);
        if(osf->isPrimitive()){
            continue;
        }
        writeObject0(osf->getField()->get(obj));
    }
}

void JObjectOutputStream::writeClassDescriptor(JObjectStreamClass* desc){
    desc->writeNonProxy(this);
}

void JObjectOutputStream::writeTypeString(JString* str){
    qint32 handle;
    if(str->getString().size() == 0){
        writeNull();
    } else if((handle = handles->lookup(str) != -1)){
        writeHandle(handle);
    } else{
        writeString(str);
    }
}

void JObjectOutputStream::writeTypeString(string str){
    if(str.size() == 0){
        writeNull();
    } else{
        writeString(str);
    }
}

void JObjectOutputStream::writeNull(){
    bout->writeByte(TC_NULL);
}

void JObjectOutputStream::writeString(JString* str){
    handles->assign(str);
    qint64 utflen = bout->getUTFLength(str->getString());
    if(utflen <= 0xFFFF){
        bout->writeByte(TC_STRING);
        bout->writeUTF(str->getString(), utflen);
    }else{
        bout->writeByte(TC_LONGSTRING);
        bout->writeLongUTF(str->getString(), utflen);
    }
}

void JObjectOutputStream::writeString(string str){
    qint64 utflen = bout->getUTFLength(str);
    if(utflen <= 0xFFFF){
        bout->writeByte(TC_STRING);
        bout->writeUTF(str, utflen);
    }else{
        bout->writeByte(TC_LONGSTRING);
        bout->writeLongUTF(str, utflen);
    }
}

void JObjectOutputStream::writeUTF(string str){
    bout->writeUTF(str);
}


void JObjectOutputStream::writeBytes(string str){
    bout->writeBytes(str);
}

void JObjectOutputStream::writeChars(string str){
    bout->writeChars(str);
}

void JObjectOutputStream::writeSerialVersionUID(){
    /* Should implement the serial version UID generation algorithm. */
    writeLong(1);
}

JObjectOutputStream::~JObjectOutputStream(){
    delete handles;
    delete bout;
    //delete[] fields; TODO
    //TODO delete fields;
    delete curContext;
}
