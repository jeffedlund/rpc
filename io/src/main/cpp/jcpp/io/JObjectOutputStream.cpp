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

JObjectOutputStream::JObjectOutputStream(){
    handles = new OutputHandleTable();
}

JObjectOutputStream::JObjectOutputStream(JOutputStream* out){
    handles=new OutputHandleTable();
    depth = 0;
    enableOverride = false;
    enableReplaceObject(false);

    this->bout = new JBlockDataOutputStream(out);
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
        }catch(JIOException e){
            if (depth == 0) {
    //            writeFatalException(ex);
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
    try{
        if(obj == NULL)
            writeNull();
        else{
            int handle;
            if( (handle = handles->lookup(obj) != -1) ){
                writeHandle(handle);
            }else{
                JObjectStreamClass* desc = JObjectStreamClass::lookup(obj);
                curContext = new SerialCallbackContext();
                curContext->setContext(obj,desc);
                if(obj->getClass()->isArray()){
                    writeArray(obj,desc);
                } else if (obj->getClass()->isEnum()){
                     writeEnum(obj, desc);
                }
                else{
                    writeOrdinaryObject(obj,desc);
                }
            }
        }
        depth--;
        bout->setBlockDataMode(oldMode);

    } catch(JException e) {
        depth--;
        bout->setBlockDataMode(oldMode);
        throw e;
    }
}

JObject *JObjectOutputStream::replaceObject(JObject *obj) {
    return obj;
}

void JObjectOutputStream::writeOrdinaryObject(JObject* obj, JObjectStreamClass* desc, bool unshared){
    writeByte(TC_OBJECT);
    writeClassDesc(desc);
    handles->assign(obj);

    if(!desc->isProxy()){
        writeSerialData(obj, desc);
    }
}

void JObjectOutputStream::writeClassDesc(JObjectStreamClass* desc, bool unshared){
    qint32 handle;
    if(desc == NULL){
        writeNull();
    } else if( (handle = handles->lookup(desc)) != -1) {
        writeHandle(handle);
    } else if(desc->isProxy()){
        writeProxyDesc(desc, unshared);
    } else{
        writeNonProxyDesc(desc, unshared);
    }
}

void JObjectOutputStream::writeProxyDesc(JObjectStreamClass *desc, bool unshared){
    bout->writeByte(TC_PROXYCLASSDESC);
    handles->assign(unshared?NULL:desc);
    JClass* cl=desc->getJClass();
    vector<JClass*>* interfaces=cl->getInterfaces();
    bout->writeInt(interfaces->size());
    for(unsigned int i = 0; i < interfaces->size(); ++i){
        JClass* clazz=interfaces->at(i);
        bout->writeUTF(clazz->getName());
    }
    delete interfaces; // Tests.
    bout->setBlockDataMode(true);
    bout->setBlockDataMode(false);
    bout->writeByte(TC_ENDBLOCKDATA);
    writeClassDesc(desc->getSuperDesc(), false);
}

void JObjectOutputStream::writeHandle(qint32 handle){
    bout->writeByte(TC_REFERENCE);
    bout->writeInt(baseWireHandle + handle);
}

void JObjectOutputStream::writeEnum(JObject *obj, JObjectStreamClass* desc){
    bout->writeByte(TC_ENUM);
    writeClassDesc(desc);
    handles->assign(obj);
    writeString( ((JEnum*)obj)->getName());
}

void JObjectOutputStream::writeNonProxyDesc(JObjectStreamClass* desc, bool unshared){
    bout->writeByte(TC_CLASSDESC);
    handles->assign(desc);
    writeClassDescriptor(desc);
    bout->setBlockDataMode(true);
    bout->setBlockDataMode(false);
    bout->writeByte(TC_ENDBLOCKDATA);
    writeClassDesc(desc->getSuperDesc());
}

void JObjectOutputStream::writeSerialData(JObject *obj, JObjectStreamClass* desc){
        desc->getClassDataLayout();
        int size = desc->getHierarchy()->size() - 1;
        for(int i = size; i >= 0 ; --i){
            JObjectStreamClass* slotDesc = (*desc->getHierarchy())[i];
            if (slotDesc->hasWriteObjectMethod()){
                bout->setBlockDataMode(true);
                //((JSerializable*)obj)->writeObject(this);//TODO bugged
                bout->setBlockDataMode(false);
                bout->writeByte(TC_ENDBLOCKDATA);
            }else{
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

void JObjectOutputStream::writeArray(JObject *obj, JObjectStreamClass* desc, bool unshared){
    bout->writeByte(TC_ARRAY);
    writeClassDesc(desc);
    handles->assign(obj);

    writeArrayProperties(obj);
}

/**
  * Writes given array properties to stream.
  */
void JObjectOutputStream::writeArrayProperties(JObject* array){
    //TODO
//    JClass* _class=array->getClass();
//    string component = _class->getComponentType();
//    bout->writeInt(array->getLength());
//    QVariant* var = array->getArray();
//    if(component.compare("qint32") == 0){
//        qint32* ia = var->value<qint32*>();
//        bout->writeInts(ia, 0, array->getLength());
//        delete[] ia;

//    }else if(component.compare("qint64") == 0){
//        qint64* ia = var->value<qint64*>();
//        bout->writeLongs(ia, 0, array->getLength());
//        delete[] ia;

//    }else if(component.compare("qint16") == 0){
//        qint16* ia = var->value<qint16*>();
//        bout->writeShorts(ia, 0, array->getLength());

//    }else if(component.compare("quint16") == 0){
//        quint16* ia = var->value<quint16*>();
//        bout->writeChars(ia, 0, array->getLength());
//        delete[] ia;

//    }else if(component.compare("qint8") == 0){
//        qint8* ia = var->value<qint8*>();
//        bout->write(ia, 0, array->getLength(), true);
//        delete[] ia;

//    }else if(component.compare("float") == 0){
//        float* ia = var->value<float*>();
//        bout->writeFloats(ia, 0, array->getLength());
//        delete[] ia;

//    }else if(component.compare("double") == 0){
//        double* ia = var->value<double*>();
//        bout->writeDoubles(ia, 0, array->getLength());
//        delete[] ia;
//    }
//    else{
//        JObject** ja = JObject::getObjectArrayFromQVariant(var);
//        delete var;
//        for(int i = 0; i < array->getLength(); ++i){
//            writeObject0(ja[i]);
//            delete ja[i];
//        }
//        delete[] ja;
//    }
}

void JObjectOutputStream::defaultWriteFields(JObject *obj, JObjectStreamClass* desc){
    int primDataSize = desc->getPrimDataSize();
    primVals = new qint8[primDataSize];
    desc->getPrimFieldValues(obj, primVals,this);
//    bout->write(primVals, 0, primDataSize, false);//TODO

    if(desc->getNumObjFields() > 0)
        writeObjectValues(obj, desc);
}

void JObjectOutputStream::writePrimitiveData(JObject *obj, JObjectStreamClass *desc){
    int primDataSize = desc->getPrimDataSize();
    if (primVals == NULL || sizeof(primVals) < primDataSize) {
        primVals = new qint8[primDataSize];
    }
    desc->getPrimFieldValues(obj, primVals,this);
//    bout->write(primVals, 0, primDataSize, false);
}

void JObjectOutputStream::writeObjectValues(JObject *obj, JObjectStreamClass *desc){//TODO
//    vector<JObjectStreamField*>* fields = desc->getFields();
//    for(int i = 0; i < fields->size(); i++){
//        JObjectStreamField* osf = fields[i];
//        if(osf->isPrimitive()){
//            continue;
//        }

//        writeObject0(j);
//        delete osf;
//    }
}

void JObjectOutputStream::writeClassDescriptor(JObjectStreamClass* desc){
    desc->writeNonProxy(this);
}

void JObjectOutputStream::writeTypeString(string str){
    qint32 handle;
    if(str.size() == 0){
        writeNull();
    } else if((handle = handles->lookup(NULL/*TODO which param? str*/)) != -1){
        writeHandle(handle);
    } else{
        writeString(str);
    }
}

void JObjectOutputStream::writeNull(){
    bout->writeByte(TC_NULL);
}

void JObjectOutputStream::writeString(string str, bool unshared){
    handles->assign(NULL/*TODO whih param ?str*/);
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
