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
#include "JLANG.h"
#include "JExternalizable.h"
#include "Object.h"
#include "Collections.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JObjectOutputStreamClass : public JClass{
        public:
            JObjectOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectOutputStream";
                name="java.io.ObjectOutputStream";
                simpleName="ObjectOutputStream";
            }

            JClass* getSuperclass(){
                return JOutputStream::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of class "+getName());
            }
        };

        static JClass* clazz;

        JClass* JObjectOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectOutputStreamClass();
            }
            return clazz;
        }

        JObjectOutputStream::JObjectOutputStream(JOutputStream* out):JOutputStream(getClazz()){
            init(out);
        }

        JObjectOutputStream::JObjectOutputStream(JOutputStream* out,JClass* _class):JOutputStream(_class){
            init(out);
        }

        void JObjectOutputStream::init(JOutputStream* out){
            this->bout = new JBlockDataOutputStream(out);
            handles=new OutputHandleTable();
            outputClassLoader=NULL;
            enableOverride = false;
            enableReplaceObject(false);
            depth = 0;
            writeStreamHeader();
            bout->setBlockDataMode(true);
            this->lengthPrimVals=0;
            this->primVals=NULL;
            curContext=NULL;
        }

        bool JObjectOutputStream::enableReplaceObject(bool enable) {
            if (enable == enableReplace) {
                return enable;
            }
            enableReplace = enable;
            return !enableReplace;
        }

        void JObjectOutputStream::writeBoolean(JPrimitiveBoolean* b){
            writeBoolean(b->get());
        }

        void JObjectOutputStream::writeByte(JPrimitiveByte* b){
            writeByte(b->get());
        }

        void JObjectOutputStream::writeChar(JPrimitiveChar* c){
            writeChar(c->get());
        }

        void JObjectOutputStream::writeDouble(JPrimitiveDouble* d){
            writeDouble(d->get());
        }

        void JObjectOutputStream::writeFloat(JPrimitiveFloat* f){
            writeFloat(f->get());
        }

        void JObjectOutputStream::writeLong(JPrimitiveLong* l){
            writeLong(l->get());
        }

        void JObjectOutputStream::writeShort(JPrimitiveShort* s){
            writeShort(s->get());
        }

        void JObjectOutputStream::writeInt(JPrimitiveInt* i){
            writeInt(i->get());
        }

        void JObjectOutputStream::writeBoolean(jbool b){
            bout->writeBoolean(b);
        }

        void JObjectOutputStream::writeByte(jint b){
            bout->writeByte(b);
        }

        void JObjectOutputStream::write(jint b){
            bout->write(b);
        }

        void JObjectOutputStream::write(jbyte b[], int off, int len){
            bout->write(b,off,len);
        }

        void JObjectOutputStream::writeChar(jint v){
            bout->writeChar(v);
        }

        void JObjectOutputStream::writeDouble(jdouble v){
            bout->writeDouble(v);
        }

        void JObjectOutputStream::writeFloat(jfloat v){
            bout->writeFloat(v);
        }

        void JObjectOutputStream::writeShort(jint v){
            bout->writeShort(v);
        }

        void JObjectOutputStream::writeInt(jint v){
            bout->writeInt(v);
        }

        void JObjectOutputStream::writeLong(jlong v){
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
                    if (obj->getClass()==JString::getClazz()){
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
            jint handle;
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

        void JObjectOutputStream::writeHandle(jint handle){
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
            //annotateClass
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
            for (unsigned int i=0;i<classDataSlots->size();i++){
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
                        JPrimitiveInt* ji=(JPrimitiveInt*)primitiveArray->get(i);
                        bout->writeInt(ji->get());
                    }
                }else if (ccl==JPrimitiveByte::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveByte* jb=(JPrimitiveByte*)primitiveArray->get(i);
                        bout->writeByte(jb->get());
                    }
                }else if (ccl==JPrimitiveLong::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveLong* jl=(JPrimitiveLong*)primitiveArray->get(i);
                        bout->writeLong(jl->get());
                    }
                }else if (ccl==JPrimitiveFloat::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveFloat* jf=(JPrimitiveFloat*)primitiveArray->get(i);
                        bout->writeFloat(jf->get());
                    }
                }else if (ccl==JPrimitiveDouble::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveDouble* jd=(JPrimitiveDouble*)primitiveArray->get(i);
                        bout->writeDouble(jd->get());
                    }
                }else if (ccl==JPrimitiveShort::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveShort* js=(JPrimitiveShort*)primitiveArray->get(i);
                        bout->writeShort(js->get());
                    }
                }else if (ccl==JPrimitiveChar::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveChar* jc=(JPrimitiveChar*)primitiveArray->get(i);
                        bout->writeChar(jc->get());
                    }
                }else if (ccl==JPrimitiveBoolean::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveBoolean* jb=(JPrimitiveBoolean*)primitiveArray->get(i);
                        bout->writeBoolean(jb->get());
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
            delete[] primVals;
            primVals = new jbyte[primDataSize];
            lengthPrimVals=primDataSize;
            desc->writePrimFieldValues(obj, primVals,this);

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
            if (primVals == NULL || lengthPrimVals < primDataSize) {
                if (primVals!=NULL){
                    delete[] primVals;
                }
                primVals = new jbyte[primDataSize];
                lengthPrimVals=primDataSize;
            }
            desc->writePrimFieldValues(obj, primVals,this);
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
            jint handle;
            if(str==NULL){
                writeNull();
            } else if((handle = handles->lookup(str) != -1)){
                writeHandle(handle);
            } else{
                writeString(str);
            }
        }

        void JObjectOutputStream::writeNull(){
            bout->writeByte(TC_NULL);
        }

        void JObjectOutputStream::writeString(JString* str){
            handles->assign(str);
            jlong utflen = bout->getUTFLength(str->getString());
            if(utflen <= 0xFFFF){
                bout->writeByte(TC_STRING);
                bout->writeUTF(str->getString(), utflen);
            }else{
                bout->writeByte(TC_LONGSTRING);
                bout->writeLongUTF(str->getString(), utflen);
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
            delete curContext;
            delete[] primVals;
        }
    }
}
