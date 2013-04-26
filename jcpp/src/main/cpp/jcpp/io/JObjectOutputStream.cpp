#include "JObjectOutputStream.h"

#include <iostream>
#include "JObjectOutputStream.h"
#include "JBlockDataOutputStream.h"
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
#include "JNotActiveException.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JObjectOutputStreamClass : public JClass{
        public:
            JObjectOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectOutputStream";
                name="java.io.ObjectOutputStream";
                simpleName="ObjectOutputStream";
                addInterface(JObjectOutput::getClazz());
                addInterface(JObjectStreamConstants::getClazz());
            }

            JClass* getSuperclass(){
                return JOutputStream::getClazz();
            }

            virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JObjectOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectOutputStreamClass();
            }
            return clazz;
        }


        class JPutFieldClass : public JClass{
        public:
            JPutFieldClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectOutputStream$PutField";
                name="java.io.ObjectOutputStream$PutField";
                simpleName="ObjectOutputStream$PutField";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual JClass* getDeclaringClass(){
                return JObjectOutputStream::getClazz();
            }
        };

        static JClass* putFieldClazz;
        JClass* JObjectOutputStream::JPutField::getClazz(){
            if (putFieldClazz==NULL){
                putFieldClazz=new JPutFieldClass();
            }
            return putFieldClazz;
        }

        JObjectOutputStream::JPutField::~JPutField(){
        }

        class JPutFieldImplClass : public JClass{
        public:
            JPutFieldImplClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectOutputStream$PutFieldImpl";
                name="java.io.ObjectOutputStream$PutFieldImpl";
                simpleName="ObjectOutputStream$PutFieldImpl";
            }

            JClass* getSuperclass(){
                return JObjectOutputStream::JPutField::getClazz();
            }

            virtual JClass* getDeclaringClass(){
                return JObjectOutputStream::getClazz();
            }
        };

        static JClass* putFieldImplClazz;
        class JPutFieldImpl : public JObjectOutputStream::JPutField{
        protected:
            JObjectOutputStream* s;
            JObjectStreamClass* desc;
            jbyte* primVals;
            JObject** objVals;

        public:
            JPutFieldImpl(JObjectOutputStream* s,JObjectStreamClass* desc):JPutField(getClazz()){
                this->s=s;
                this->desc=desc;
                primVals=new jbyte[desc->getPrimDataSize()];
                objVals=new JObject*[desc->getNumObjFields()];
            }

            static JClass* getClazz(){
                if (putFieldImplClazz==NULL){
                    putFieldImplClazz=new JPutFieldImplClass();
                }
                return putFieldImplClazz;
            }

            virtual void put(string name, bool val){
                JBits::putBoolean(primVals,getFieldOffset(name,JBoolean::TYPE),val);
            }

            virtual void put(string name, jbyte val){
                primVals[getFieldOffset(name,JByte::TYPE)]=val;
            }

            virtual void put(string name, jchar val){
                JBits::putChar(primVals,getFieldOffset(name,JChar::TYPE),val);
            }

            virtual void put(string name, jshort val){
                JBits::putShort(primVals,getFieldOffset(name,JShort::TYPE),val);
            }

            virtual void put(string name, jint val){
                JBits::putInt(primVals,getFieldOffset(name,JInteger::TYPE),val);
            }

            virtual void put(string name, jfloat val){
                JBits::putFloat(primVals,getFieldOffset(name,JFloat::TYPE),val);
            }

            virtual void put(string name, jlong val){
                JBits::putLong(primVals,getFieldOffset(name,JLong::TYPE),val);
            }

            virtual void put(string name, jdouble val){
                JBits::putDouble(primVals,getFieldOffset(name,JDouble::TYPE),val);
            }

            virtual void put(string name, JObject* val){
                objVals[getFieldOffset(name,JObject::getClazz())]=val;
            }

            virtual void write(JObjectOutput *out){
                if (s!=out){
                    throw new JIllegalArgumentException("wrong stream");
                }
                out->write(primVals,0,desc->getPrimDataSize());

                vector<JObjectStreamField*>* fields=desc->getFields();
                jint numPrimFields=fields->size()-desc->getNumObjFields();
                for (int i=0;i<desc->getNumObjFields();i++){
                    JObjectStreamField* f=fields->at(numPrimFields+i);
                    if (f->isUnshared()){
                        throw new JIOException("cannot write unshared object");
                    }
                    out->writeObject(objVals[i]);
                }
            }

            void writeFields(){
                s->bout->write(primVals, 0, desc->getPrimDataSize(), false);

                vector<JObjectStreamField*>* fields = desc->getFields();
                jint numPrimFields=fields->size()-desc->getNumObjFields();
                for (int i = 0; i < desc->getNumObjFields(); i++) {
                    JObjectStreamField* f=fields->at(numPrimFields + i);
                    s->writeObject0(objVals[i],f->isUnshared());
                }
            }

            jint getFieldOffset(string name, JClass* type) {
                JObjectStreamField* field = desc->getField(name, type);
                if (field == NULL) {
                    throw new JIllegalArgumentException("no such field " + name + " with type " + type->toString());
                }
                return field->getOffset();
            }

            ~JPutFieldImpl(){
                delete[] primVals;
                delete[] objVals;
            }
        };

        void JObjectOutputStreamClass::fillDeclaredClasses(){
            addDeclaredClass(JBlockDataOutputStream::getClazz());
            addDeclaredClass(JObjectOutputStream::JPutField::getClazz());
            addDeclaredClass(JPutFieldImpl::getClazz());
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
            curPut=NULL;
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

        void JObjectOutputStream::writeUnshared(JObject* object){
            try{
                writeObject0(object,true);
            }catch(JIOException* ex){
                if (depth==0){
                    writeFatalException(ex);
                }
                throw ex;
            }
        }

        void JObjectOutputStream::writeObject(JObject *obj){
            if(enableOverride)
                writeObjectOverride(obj);
            else{
                try{
                    writeObject0(obj,false);
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

        void JObjectOutputStream::writeObject0(JObject* obj,jbool unshared){
            bool oldMode = bout->setBlockDataMode(false);
            depth++;
            if(obj == NULL){
                writeNull();
            }else{
                int handle;
                if(!unshared && (handle = handles->lookup(obj) != -1) ){
                    writeHandle(handle);
                }else if (JClass::getClazz()->isAssignableFrom(obj->getClass())){
                    writeClass((JClass*)obj,unshared);
                }else if (JObjectStreamClass::getClazz()->isAssignableFrom(obj->getClass())){
                    writeClassDesc((JObjectStreamClass*)obj,unshared);
                }else{
                    JObject* orig = obj;
                    JClass* cl = obj->getClass();
                    JObjectStreamClass* desc=NULL;
                    for (;;) {
                        JClass* repCl;
                        desc = JObjectStreamClass::lookup(cl,true);
                        if (desc==NULL || !desc->hasWriteReplaceMethod() ||
                            (obj = desc->invokeWriteReplace(obj)) == NULL|| (repCl = obj->getClass()) == cl){
                            break;
                        }
                        cl = repCl;
                    }
                    if (enableReplace) {
                        JObject* rep = replaceObject(obj);
                        if (rep != obj && rep != NULL) {
                            cl = rep->getClass();
                            desc = JObjectStreamClass::lookup(cl,true);
                        }
                        obj = rep;
                    }

                    bool avoid=false;
                    if (obj != orig) {
                        if (obj == NULL) {
                            writeNull();
                            avoid=true;
                        }else{
                            desc=JObjectStreamClass::lookup(obj->getClass(),true);
                            if(!unshared && (handle = handles->lookup(obj) != -1) ){
                                writeHandle(handle);
                                avoid=true;
                            }else if (JClass::getClazz()->isAssignableFrom(obj->getClass())){
                                writeClass((JClass*)obj,unshared);
                                avoid=true;
                            }else if (JObjectStreamClass::getClazz()->isAssignableFrom(obj->getClass())){
                                writeClassDesc((JObjectStreamClass*)obj,unshared);
                                avoid=true;
                            }
                        }
                    }
                    if (!avoid){
                        if (obj->getClass()==JString::getClazz()){
                            writeString((JString*)obj,unshared);
                        }else if(obj->getClass()->isArray()){
                            writeArray(obj,desc,unshared);
                        } else if (obj->getClass()->isEnum()){
                             writeEnum(obj, desc,unshared);
                        }else if (JSerializable::getClazz()->isAssignableFrom(obj->getClass())){
                            writeOrdinaryObject(obj,desc,unshared);
                        }else{
                            throw new JNotSerializableException(obj->getClass()->getName());
                        }
                    }
                }
            }
            depth--;
            bout->setBlockDataMode(oldMode);
        }

        JObject *JObjectOutputStream::replaceObject(JObject *obj) {
            return obj;
        }

        void JObjectOutputStream::writeOrdinaryObject(JObject* obj, JObjectStreamClass* desc,jbool unshared){
            writeByte(TC_OBJECT);
            writeClassDesc(desc,false);
            handles->assign((unshared?NULL : obj));

            if (desc->isExternalizable() && !desc->isProxy()){
                writeExternalData(obj);
            }else{
                writeSerialData(obj,desc);
            }
        }

        void JObjectOutputStream::writeClass(JClass* cl,jbool unshared){
            bout->writeByte(TC_CLASS);
            writeClassDesc(JObjectStreamClass::lookup(cl,true),false);
            handles->assign((unshared ? NULL : cl));
        }

        void JObjectOutputStream::writeClassDesc(JObjectStreamClass* desc,jbool unshared){
            jint handle;
            if(desc == NULL){
                writeNull();
            } else if(!unshared && (handle = handles->lookup(desc)) != -1) {
                writeHandle(handle);
            } else if(desc->isProxy()){
                writeProxyDesc(desc,unshared);
            } else{
                writeNonProxyDesc(desc,unshared);
            }
        }

        void JObjectOutputStream::writeProxyDesc(JObjectStreamClass *desc,jbool unshared){
            bout->writeByte(TC_PROXYCLASSDESC);
            handles->assign((unshared?NULL :desc));

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
            writeClassDesc(desc->getSuperDesc(),false);
        }

        void JObjectOutputStream::writeHandle(jint handle){
            bout->writeByte(TC_REFERENCE);
            bout->writeInt(baseWireHandle + handle);
        }

        void JObjectOutputStream::writeEnum(JObject *obj, JObjectStreamClass* desc,jbool unshared){
            bout->writeByte(TC_ENUM);
            JObjectStreamClass* sdesc=desc->getSuperDesc();
            writeClassDesc((sdesc->getJClass()==JEnum::getClazz()?desc:sdesc),false);
            handles->assign((unshared?NULL : obj));
            writeString( ((JEnum*)obj)->getName(),false);
        }

        void JObjectOutputStream::writeNonProxyDesc(JObjectStreamClass* desc,jbool unshared){
            bout->writeByte(TC_CLASSDESC);
            handles->assign((unshared?NULL : desc));
            writeClassDescriptor(desc);
            bout->setBlockDataMode(true);
            //annotateClass
            bout->setBlockDataMode(false);
            bout->writeByte(TC_ENDBLOCKDATA);
            writeClassDesc(desc->getSuperDesc(),false);
        }

        void JObjectOutputStream::writeExternalData(JObject* obj){
            JPutField* oldPut=curPut;
            curPut=NULL;

            SerialCallbackContext* oldContext=curContext;
            curContext=NULL;
            bout->setBlockDataMode(true);
            (dynamic_cast<JExternalizable*>(obj))->writeExternal(this);
            bout->setBlockDataMode(false);
            bout->writeByte(TC_ENDBLOCKDATA);
            curContext=oldContext;
            curPut=oldPut;
        }

        void JObjectOutputStream::writeSerialData(JObject *obj, JObjectStreamClass* desc){
            vector<JObjectStreamClass::ClassDataSlot*>* classDataSlots=desc->getClassDataLayout();
            for (unsigned int i=0;i<classDataSlots->size();i++){
                JObjectStreamClass::ClassDataSlot* dataSlot=classDataSlots->at(i);
                JObjectStreamClass* slotDesc=dataSlot->desc;
                if (slotDesc->hasWriteObjectMethod()) {
                    JPutField* oldPut=curPut;
                    curPut=NULL;
                    SerialCallbackContext* oldContext = curContext;
                    curContext = new SerialCallbackContext();
                    curContext->setContext(obj, slotDesc);
                    bout->setBlockDataMode(true);
                    slotDesc->invokeWriteObject(obj, this);
                    bout->setBlockDataMode(false);
                    bout->writeByte(TC_ENDBLOCKDATA);
                    delete curContext;
                    curContext = oldContext;
                    curPut=oldPut;
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

        JObjectOutputStream::JPutField* JObjectOutputStream::putFields(){
            if (curPut==NULL){
                if (curContext==NULL){
                    throw new JNotActiveException("not in call to writeObject");
                }
                curContext->getObj();
                JObjectStreamClass* curDesc=curContext->getDesc();
                curPut=new JPutFieldImpl(this,curDesc);
            }
            return curPut;
        }

        void JObjectOutputStream::writeFields(){
            if (curPut==NULL){
                throw new JNotActiveException("no current PutField object");
            }
            bout->setBlockDataMode(false);
            JPutFieldImpl* impl=dynamic_cast<JPutFieldImpl*>(curPut);
            impl->writeFields();
            bout->setBlockDataMode(true);
        }

        void JObjectOutputStream::writeArray(JObject *obj, JObjectStreamClass* desc,jbool unshared){
            bout->writeByte(TC_ARRAY);
            writeClassDesc(desc,false);
            handles->assign((unshared?NULL : obj));

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
                        bout->writeInt((ji!=NULL ? ji->get() : (jint)0));
                    }
                }else if (ccl==JPrimitiveByte::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveByte* jb=(JPrimitiveByte*)primitiveArray->get(i);
                        bout->writeByte((jb!=NULL ? jb->get() : (jbyte)0));
                    }
                }else if (ccl==JPrimitiveLong::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveLong* jl=(JPrimitiveLong*)primitiveArray->get(i);
                        bout->writeLong((jl!=NULL ? jl->get() : (jlong)0));
                    }
                }else if (ccl==JPrimitiveFloat::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveFloat* jf=(JPrimitiveFloat*)primitiveArray->get(i);
                        bout->writeFloat((jf!=NULL ? jf->get() : (jfloat)0));
                    }
                }else if (ccl==JPrimitiveDouble::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveDouble* jd=(JPrimitiveDouble*)primitiveArray->get(i);
                        bout->writeDouble((jd!=NULL ? jd->get() : (jdouble)0));
                    }
                }else if (ccl==JPrimitiveShort::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveShort* js=(JPrimitiveShort*)primitiveArray->get(i);
                        bout->writeShort((js!=NULL ? js->get() : (jshort)0));
                    }
                }else if (ccl==JPrimitiveChar::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveChar* jc=(JPrimitiveChar*)primitiveArray->get(i);
                        bout->writeChar((jc!=NULL ? jc->get() : (jchar)0));
                    }
                }else if (ccl==JPrimitiveBoolean::getClazz()){
                    for (int i=0;i<primitiveArray->size();i++){
                        JPrimitiveBoolean* jb=(JPrimitiveBoolean*)primitiveArray->get(i);
                        bout->writeBoolean((jb!=NULL ? jb->get() : false));
                    }
                }else{
                    throw new JInternalError();
                }
            }else{
                for (int i=0;i<primitiveArray->size();i++){
                    writeObject0(primitiveArray->get(i),false);
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
            writeObject0(ex,false);
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
                writeObject0(osf->getField()->get(obj),osf->isUnshared());
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
                writeString(str,false);
            }
        }

        void JObjectOutputStream::writeNull(){
            bout->writeByte(TC_NULL);
        }

        void JObjectOutputStream::writeString(JString* str,jbool unshared){
            handles->assign((unshared?NULL : str));
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
            if (curPut!=NULL){
                delete curPut;
            }
            delete curContext;
            delete[] primVals;
        }
    }
}
