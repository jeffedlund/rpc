#include "JObjectStreamClass.h"
#include "JObjectStreamConstants.h"
#include "JObjectStreamField.h"
//#include "JObjectInputStream.h"
#include "JClass.h"
#include "JField.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveShort.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveDouble.h"
#include "JInvalidClassException.h"
#include "JInternalError.h"
#include "JUnsupportedOperationException.h"
#include "JBits.h"
#include "JSerializable.h"
#include "JExternalizable.h"
#include "JVoid.h"
#include "JNullPointerException.h"
#include "Collections.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include "JNotSerializableException.h"
#include "Object.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JObjectStreamClassClass : public JClass{
            public:
              JObjectStreamClassClass(){
                  this->canonicalName="java.io.ObjectStreamClass";
                  this->name="java.io.ObjectStreamClass";
                  this->simpleName="ObjectStreamClass";
                  this->serialVersionUID=6120832682080437368ULL;
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              JObject* newInstance(){
                  return new JObjectStreamClass();
              }
        };

        static JClass* clazz;

        JClass* JObjectStreamClass::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectStreamClassClass();
            }
            return clazz;
        }

        static map<JClass*, JObjectStreamClass*>* allObjectStreamClass;

        JObjectStreamClass* JObjectStreamClass::lookup(JClass* meta){
            if(meta == NULL){
                return NULL;
            }
            if (!JSerializable::getClazz()->isAssignableFrom(meta)){
                return NULL;
            }
            JObjectStreamClass* desc=NULL;
            if (allObjectStreamClass==NULL){
                allObjectStreamClass=new map<JClass*,JObjectStreamClass*>();
            }
            if (allObjectStreamClass->count(meta)==1){
                desc=allObjectStreamClass->at(meta);
            }
            if (desc==NULL){
                desc = new JObjectStreamClass(meta);
                allObjectStreamClass->insert(pair<JClass*,JObjectStreamClass*>(meta, desc));
            }
            return desc;
        }

        JObjectStreamClass::JObjectStreamClass():JObject(getClazz()){
            this->name="";
            this->suid=-1;
            this->bIsProxy=false;
            this->bIsEnum=false;
            this->serializable=false;
            this->externalizable=false;
            this->writeObjectData=false;
            this->blockExternalData=true;
            this->primDataSize=0;
            this->numObjFields=0;
            this->fields = NULL;
            this->superDesc=NULL;
            this->resolveEx=NULL;
            this->jClass=NULL;
            this->readObjectMethod=NULL;
            this->dataLayout=NULL;
        }

        static vector<JObjectStreamField*>* getDefaultSerialFields(JClass* cl) {
            vector<JField*>* clFields = cl->getDeclaredFields();
            if (clFields!=NULL){
                vector<JObjectStreamField*>* fields=new vector<JObjectStreamField*>;
                for (unsigned int i = 0; i < clFields->size(); i++) {
                    JField* f=clFields->at(i);
                    if (true){//TODO !f->isStatic() && !f->isTransient()) {
                        JObjectStreamField* ff=new JObjectStreamField(f,false,true);
                        fields->push_back(ff);
                    }
                }
                if (fields->size()==0){
                    return NULL;
                }else{
                    return fields;
                }
            }
            return NULL;
        }

        static vector<JObjectStreamField*>* getSerialFields(JClass* cl){
            vector<JObjectStreamField*>* fields=NULL;
            if (JSerializable::getClazz()->isAssignableFrom(cl) && !JExternalizable::getClazz()->isAssignableFrom(cl) &&
                !cl->isProxy() && !cl->isInterface()){
                fields = getDefaultSerialFields(cl);
                if (fields!=NULL){
                    sort(fields->begin(),fields->end(),JObjectStreamField::comparator);
                }
           }
           return fields;
        }

        JObjectStreamClass::JObjectStreamClass(JClass* _class):JObject(getClazz()){
            this->primDataSize = 0;
            this->numObjFields = 0;
            this->jClass=_class;
            this->name = _class->getName();
            this->bIsProxy=_class->isProxy();
            this->bIsEnum = _class->isEnum();
            this->serializable=JSerializable::getClazz()->isAssignableFrom(_class);
            this->externalizable=JExternalizable::getClazz()->isAssignableFrom(_class);
            this->suid=0;
            this->writeObjectData=false;
            this->blockExternalData=true;
            this->superDesc=NULL;
            this->resolveEx=NULL;
            this->readObjectMethod=NULL;
            this->writeObjectMethod=NULL;
            this->dataLayout=NULL;


            JClass* superCl=_class->getSuperclass();
            superDesc=(superCl != NULL)?lookup(superCl):NULL;
            if (serializable){
                if (bIsEnum) {
                    suid = 0;
                    fields = NULL;
                    return;
                }
                if (_class->isArray()) {
                    fields = NULL;
                    return;
                }

                suid = _class->getSerialVersionUID();
                fields = getSerialFields(_class);
                computeFieldOffsets();

                if (_class->hasMethod("writeObject",NULL)){
                    this->writeObjectMethod=_class->getMethod("writeObject",NULL);
                    writeObjectData=writeObjectMethod!=NULL;
                }
                if (_class->hasMethod("readObject",NULL)){
                    this->readObjectMethod=_class->getMethod("readObject",NULL);
                }
            }else{
                suid=0;
                fields=NULL;
            }
        }

        bool JObjectStreamClass::isEnum(){
            return bIsEnum;
        }

        bool JObjectStreamClass::isProxy(){
            return bIsProxy;
        }

        bool JObjectStreamClass::hasReadObjectMethod() {
            return readObjectMethod!=NULL;
        }

        bool JObjectStreamClass::hasWriteObjectMethod(){
            return writeObjectMethod!=NULL;
        }

        bool JObjectStreamClass::hasWriteObjectData() {
            return writeObjectData;
        }

        bool JObjectStreamClass::isExternalizable(){
            return this->externalizable;
        }

        bool JObjectStreamClass::hasBlockExternalData(){
            return this->blockExternalData;
        }

        JClass* JObjectStreamClass::getJClass(){
            return jClass;
        }

        jshort JObjectStreamClass::getNumFields(){
            return (fields==NULL?0:fields->size());
        }

        jint JObjectStreamClass::getNumObjFields(){
            return numObjFields;
        }

        JObjectStreamField* JObjectStreamClass::getField(int i){
            if (fields == NULL) {
                throw new JInternalError("no fields!");
            }
            return fields->at(i);
        }

        string JObjectStreamClass::getName(){
            return name;
        }

        int JObjectStreamClass::getPrimDataSize(){
            return primDataSize;
        }

        JObjectStreamClass *JObjectStreamClass::getSuperDesc(){
            return superDesc;
        }

        JClassNotFoundException* JObjectStreamClass::getResolveException(){
            return resolveEx;
        }

        void JObjectStreamClass::readNonProxy(JObjectInputStream *in) {
            name = in->readUTF();
            suid = in->readLong();
            bIsProxy = false;

            jbyte flags = in->readByte();
            writeObjectData = ((flags & JObjectStreamConstants::SC_WRITE_METHOD) != 0);
            blockExternalData = ((flags & JObjectStreamConstants::SC_BLOCK_DATA) != 0);
            externalizable = ((flags & JObjectStreamConstants::SC_EXTERNALIZABLE) != 0);
            bool sflag = ((flags & JObjectStreamConstants::SC_SERIALIZABLE) != 0);
            if (externalizable && sflag) {
                throw new JInvalidClassException(""+name+" : serializable and externalizable flags conflict");
            }
            bIsEnum = ((flags & JObjectStreamConstants::SC_ENUM) != 0);
            serializable = externalizable || sflag;
            if (bIsEnum && suid != 0) {
                stringstream ss;
                ss<<"enum "<<name<<" descriptor has non-zero serialVersionUID: " << suid;
                throw new JInvalidClassException(ss.str());
            }

            jshort numFields = in->readShort();
            if (bIsEnum && numFields != 0) {
                stringstream ss;
                ss<<"enum "<<name<<" descriptor has non-zero field count: " << numFields;
                throw new JInvalidClassException(ss.str());
            }
            if (numFields > 0) {
                fields = new vector<JObjectStreamField*>();
                for (int i = 0; i < numFields; ++i) {
                    jchar tcode=(jchar) in->readByte();;
                    string fname=in->readUTF();
                    string signature;
                    if ((tcode=='L' || (tcode=='['))){
                        JString* readString=in->readTypeString();
                        signature=readString->getString();
                        delete readString;
                    }else{
                        signature.push_back(tcode);
                    }
                    fields->push_back(new JObjectStreamField(fname,signature,false));
                }
            }
            computeFieldOffsets();
        }

        void JObjectStreamClass::initNonProxy(JObjectStreamClass * const model,JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* superDesc){
            this->jClass = jClass;
            this->resolveEx=resolveEx;
            this->superDesc = superDesc;
            name = model->name;
            suid = model->suid;
            bIsProxy = false;
            bIsEnum = model->bIsEnum;
            serializable = model->serializable;
            externalizable = model->externalizable;
            blockExternalData= model->blockExternalData;
            writeObjectData = model->writeObjectData;
            fields = new vector<JObjectStreamField*>;
            for (int i = 0; i < model->getNumFields(); ++i) {
                fields->push_back(model->fields->at(i));
            }
            primDataSize = model->primDataSize;
            numObjFields = model->numObjFields;

            if (jClass!=NULL){
                JObjectStreamClass* localDesc=lookup(jClass);
                if (localDesc->isProxy()) {
                    throw new JInvalidClassException("cannot bind non-proxy descriptor to a proxy class");
                }
                if (bIsEnum != localDesc->isEnum()) {
                    throw new JInvalidClassException(isEnum() ? "cannot bind enum descriptor to a non-enum class" : "cannot bind non-enum descriptor to an enum class");
                }
                this->writeObjectMethod= localDesc->writeObjectMethod;
                this->readObjectMethod = localDesc->readObjectMethod;
            }
        }

        void JObjectStreamClass::initProxy(JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* superDesc) {
            this->jClass= jClass;
            this->resolveEx=resolveEx;
            this->superDesc = superDesc;
            bIsProxy = true;
            serializable = true;
            suid = 0;
            fields = NULL;
            if (jClass!=NULL){
                JObjectStreamClass* localDesc=lookup(jClass);
                if (!localDesc->isProxy()){
                    throw new JInvalidClassException("cannot bind proxy descriptor to a non-proxy class");
                }
                name = localDesc->getName();
                externalizable=localDesc->externalizable;
            }
        }

        void JObjectStreamClass::invokeReadObject(JObject* object, JObjectInputStream* in){
            if (readObjectMethod!=NULL){
                vector<JObject*> args;
                args.push_back(in);
                readObjectMethod->invoke(object,&args);
            }else{
                throw new JUnsupportedOperationException();
            }
        }

        void JObjectStreamClass::invokeWriteObject(JObject* object, JObjectOutputStream* out){
            if (writeObjectMethod!=NULL){
                vector<JObject*> args;
                args.push_back(out);
                writeObjectMethod->invoke(object,&args);
            }else{
                throw new JUnsupportedOperationException();
            }
        }

        void JObjectStreamClass::writeNonProxy(JObjectOutputStream* out){
            out->writeUTF(name);
            out->writeLong(suid);

            jbyte flags = 0;
            if (externalizable) {
                flags |= JObjectStreamConstants::SC_EXTERNALIZABLE;
            } else if (serializable) {
                flags |= JObjectStreamConstants::SC_SERIALIZABLE;
            }
            if (hasWriteObjectData()) {
                flags |= JObjectStreamConstants::SC_WRITE_METHOD;
            }
            if (isEnum()) {
                flags |= JObjectStreamConstants::SC_ENUM;
            }
            out->writeByte(flags);

            out->writeShort(getNumFields());
            for (int i = 0; i < getNumFields(); i++) {
                JObjectStreamField* f = fields->at(i);
                out->writeByte(f->getTypeCode());
                out->writeUTF(f->getName());
                if (!f->isPrimitive()) {
                    out->writeTypeString(f->getTypeString());
                }
            }
        }

        JObject *JObjectStreamClass::newInstance() {
            return jClass->newInstance();
        }

        void JObjectStreamClass::computeFieldOffsets() {
            primDataSize = 0;
            numObjFields = 0;
            int firstObjIndex = -1;

            for (int i = 0; i < getNumFields(); ++i) {
                switch (fields->at(i)->getTypeCode()) {
                case 'Z':
                case 'B':
                    fields->at(i)->setOffset(primDataSize++);
                    break;

                case 'C':
                case 'S':
                    fields->at(i)->setOffset(primDataSize);
                    primDataSize += 2;
                    break;

                case 'I':
                case 'F':
                    fields->at(i)->setOffset(primDataSize);
                    primDataSize += 4;
                    break;

                case 'J':
                case 'D':
                    fields->at(i)->setOffset(primDataSize);
                    primDataSize += 8;
                    break;

                case '[':
                case 'L':
                    fields->at(i)->setOffset(numObjFields++);
                    if (firstObjIndex == -1) {
                        firstObjIndex = i;
                    }
                    break;

                default:
                    throw new JInternalError();
                }
            }
            if (firstObjIndex != -1 && firstObjIndex + numObjFields != getNumFields()) {
                throw new JInvalidClassException(name+" : illegal field order");
            }
        }

        JObjectStreamClass* JObjectStreamClass::getVariantFor(JClass* cl) {
            if (this->jClass== cl) {
                return this;
            }
            JObjectStreamClass* desc = new JObjectStreamClass();
            if (isProxy()) {
                desc->initProxy(cl, NULL, superDesc);
            } else {
                desc->initNonProxy(this, cl, NULL, superDesc);
            }
            return desc;
        }

        vector<JObjectStreamClass::ClassDataSlot*>* JObjectStreamClass::getClassDataLayout(){
            if (dataLayout == NULL) {
                dataLayout = getClassDataLayout0();
            }
            return dataLayout;
        }

        vector<JObjectStreamClass::ClassDataSlot*>* JObjectStreamClass::getClassDataLayout0(){
            vector<JObjectStreamClass::ClassDataSlot*>* classDataSlots = new vector<JObjectStreamClass::ClassDataSlot*>;
            JClass* start = jClass;
            JClass* end = jClass;

            while (end != NULL && JSerializable::getClazz()->isAssignableFrom(end)) {
                end = end->getSuperclass();
            }

            for (JObjectStreamClass* d = this; d != NULL; d = d->superDesc) {
                string searchName = (d->getJClass() != NULL) ? d->getJClass()->getName() : d->getName();
                JClass* match = NULL;
                for (JClass* c = start; c != end; c = c->getSuperclass()) {
                    if (searchName==c->getName()) {
                        match = c;
                        break;
                    }
                }

                if (match != NULL) {
                    for (JClass* c = start; c != match; c = c->getSuperclass()) {
                        classDataSlots->push_back(new ClassDataSlot(JObjectStreamClass::lookup(c), false));
                    }
                    start = match->getSuperclass();
                }
                classDataSlots->push_back(new ClassDataSlot(d->getVariantFor(match), true));
            }

            for (JClass* c = start; c != end; c = c->getSuperclass()) {
                classDataSlots->push_back(new ClassDataSlot(JObjectStreamClass::lookup(c), false));
            }

            reverse(classDataSlots->begin(),classDataSlots->end());
            return classDataSlots;
        }

        void JObjectStreamClass::setPrimFieldValues(JObject* obj, jbyte *buf) {
            int pos = 0;
            for (int i = 0; i < getNumFields()-numObjFields; ++i) {
                JObjectStreamField* f = fields->at(i);
                switch (f->getTypeCode()) {
                    case 'Z': {
                        JPrimitiveBoolean* jPrimitiveBoolean=new JPrimitiveBoolean(JBits::getBool(buf,pos++));
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveBoolean);
                        break;

                    }case 'B':{
                        JPrimitiveByte* jPrimitiveByte=new JPrimitiveByte((jbyte) (buf[pos++]));
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveByte);
                        break;

                    }case 'C':{
                        JPrimitiveChar* jPrimitiveChar=new JPrimitiveChar((jchar) (buf[pos+1]));
                        pos += 2;
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveChar);
                        break;

                    }case 'S':{
                        JPrimitiveShort* jPrimitiveShort=new JPrimitiveShort(JBits::getShort(buf,pos));
                        pos += 2;
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveShort);
                        break;

                    }case 'I':{
                        JPrimitiveInt* jPrimitiveInt=new JPrimitiveInt(JBits::getInt(buf,pos));
                        pos += 4;
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveInt);
                        break;

                    }case 'F':{
                        JPrimitiveFloat* jPrimitiveFloat=new JPrimitiveFloat(JBits::getFloat(buf,pos));
                        pos += 4;
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveFloat);
                        break;

                    }case 'J':{
                        JPrimitiveLong* jPrimitiveLong=new JPrimitiveLong(JBits::getLong(buf,pos));
                        pos += 8;
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveLong);
                        break;

                    }case 'D':{
                        JPrimitiveDouble* jPrimitiveDouble=new JPrimitiveDouble(JBits::getDouble(buf,pos));
                        pos += 8;
                        obj->getClass()->getField(f->getName())->set(obj,jPrimitiveDouble);
                        break;

                    }default:{
                        throw new JInternalError();
                    }
                }
            }
        }

        void JObjectStreamClass::writePrimFieldValues(JObject* obj,jbyte* buf,JObjectOutputStream* out){
            if (obj==NULL){
                throw new JNullPointerException();
            }
            for (int i=0 ; i< getNumFields()-numObjFields ; i++){
                JObjectStreamField* f=fields->at(i);
                JField* field=obj->getClass()->getField(f->getName());
                int off=f->getOffset();
                switch(f->getTypeCode()){
                    case 'Z':{
                        JPrimitiveBoolean* b=(JPrimitiveBoolean*)field->get(obj);
                        jbool v=b->get();
                        out->writeBoolean(v);
                        JBits::putBoolean(buf, off, v);
                        break;

                    }case 'B' :{
                        JPrimitiveByte* b=(JPrimitiveByte*)field->get(obj);
                        jbyte v=b->get();
                        out->writeByte(v);
                        buf[off] = v;
                        break;

                    }case 'C':{
                        JPrimitiveChar* b=(JPrimitiveChar*)field->get(obj);
                        jchar v = b->get();
                        out->writeChar(v);
                        JBits::putChar(buf, off, v);
                        break;

                    } case 'S':{
                        JPrimitiveShort* b =(JPrimitiveShort*)field->get(obj);
                        jshort v = b->get();
                        out->writeShort(v);
                        JBits::putShort(buf, off, v);
                        break;

                    }case 'I' :{
                        JPrimitiveInt* b=(JPrimitiveInt*)field->get(obj);
                        jint v = b->get();
                        out->writeInt(v);
                        JBits::putInt(buf, off, v);
                        break;

                    }case 'F' :{
                        JPrimitiveFloat* b=(JPrimitiveFloat*)field->get(obj);
                        jfloat v = b->get();
                        out->writeFloat(v);
                        JBits::putFloat(buf, off, v);
                        break;

                    }case 'J': {
                        JPrimitiveLong* b=(JPrimitiveLong*)field->get(obj);
                        jlong v = b->get();
                        out->writeLong(v);
                        JBits::putLong(buf, off, v);
                        break;

                    }case 'D': {
                        JPrimitiveDouble* b=(JPrimitiveDouble*)field->get(obj);
                        jdouble v = b->get();
                        out->writeDouble(v);
                        JBits::putDouble(buf, off, v);
                    }
                }
            }
        }

        void JObjectStreamClass::getObjectFieldValues(JObject* jobject, JObject** values){
            if (jobject==NULL){
                throw new JNullPointerException;
            }
            for (int i=getNumFields() - numObjFields;i<getNumFields();i++){
                switch (fields->at(i)->getTypeCode() ){
                    case 'L':
                    case '[':{
                        JObject* current=jobject->getClass()->getField(fields->at(i)->getName())->get(jobject);
                        values[i-getNumFields()+numObjFields]=current;
                        break;
                    }default:
                        throw new JInternalError();
                }
            }
        }

        void JObjectStreamClass::setObjectFieldValues(JObject* jObject,JObject** values) {
            for (int i = getNumFields() - numObjFields; i < getNumFields(); ++i) {
                JObject* current = values[i-getNumFields()+numObjFields];
                jObject->getClass()->getField(fields->at(i)->getName())->set(jObject,current);
            }
        }

        string JObjectStreamClass::toString(){
            stringstream sstr;
            sstr<<"Class description :\nClass name : "<<name;
            sstr<<", SUID = "<<suid<<endl;
            sstr<<"Fields description :\nNumber of serializable fields = "<<getNumFields()<<endl;
            for (int i = 0; i < getNumFields(); ++i) {
                sstr<<"type code : "<<fields->at(i)->getTypeCode()<<", name : "<<fields->at(i)->getName()<<endl;
            }
            sstr<<"Super ";
            if (superDesc == NULL) {
                sstr<<": NULL"<<endl<<endl;
            }
            else {
                sstr<<superDesc->toString();
            }
            return sstr.str();
        }

        JObjectStreamClass::~JObjectStreamClass() {
            delete fields;
            deleteVectorOfPointers(dataLayout);
        }
    }
}
