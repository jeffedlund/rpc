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


//TODO missing methods : getSerialVersionUID,ObjectStreamClass(JClass*),writeNonProxy,
class JObjectStreamClassClass : public JClass{
    public:
      JObjectStreamClassClass(){
          this->canonicalName="java.io.ObjectStreamClass";
          this->name="java.io.ObjectStreamClass";
          this->simpleName="ObjectStreamClass";
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

static map<string, JObjectStreamClass*>* allObjectStreamClass;

JObjectStreamClass* JObjectStreamClass::lookup(JObject* obj){
    //TODO return NULL if !JSerializable
    if (allObjectStreamClass==NULL){
        allObjectStreamClass=new map<string,JObjectStreamClass*>();
    }
    if(obj == NULL){
        return NULL;
    }
    JClass* meta = obj->getClass();
    if (meta==JObject::getClazz()){
        return NULL;
    }
    string name= meta->getName();
    if (allObjectStreamClass->count(name)==1){
        return allObjectStreamClass->at(name);
    }
    JObjectStreamClass* desc = new JObjectStreamClass(meta);
    allObjectStreamClass->insert(pair<string,JObjectStreamClass*>(name, desc));
    return desc;
}

string JObjectStreamClass::getClassSignature(JClass* _class){
    stringstream ss;
    while (_class->isArray()){
        ss<<"[";
        _class=_class->getComponentType();
    }
    if (_class->isPrimitive()){
        if (_class== JPrimitiveInt::getClazz()) {
            ss<<'I';
        }else if (_class == JPrimitiveByte::getClazz()) {
            ss<<'B';
        } else if (_class == JPrimitiveLong::getClazz()) {
            ss<<'J';
        } else if (_class == JPrimitiveFloat::getClazz()) {
            ss<<'F';
        } else if (_class == JPrimitiveDouble::getClazz()) {
            ss<<'D';
        } else if (_class == JPrimitiveShort::getClazz()) {
            ss<<'S';
        } else if (_class == JPrimitiveChar::getClazz()) {
            ss<<'C';
        } else if (_class == JPrimitiveBoolean::getClazz()) {
            ss<<'Z';
        } else if (_class == JVoid::getClazz()) {//TODO
            ss<<'V';
        } else {
            throw new JInternalError();
        }
    }else{
        string name=_class->getName();//TODO replace '.' by '/'
        ss<<'L'<<name<<";";
    }
    return ss.str();
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
    this->numFields=0;
    this->primDataSize=0;
    this->numObjFields=0;
    this->fields = NULL;
    this->hierarchy = new vector<JObjectStreamClass*>();
    this->superDesc=NULL;
    this->resolveEx=NULL;
    this->jClass=NULL;
    this->readObjectMethod=NULL;
}

static JObjectStreamField** createFields(JClass* cl) {
    vector<JField*>* clFields = cl->getFields();
    if (clFields!=NULL){
        vector<JObjectStreamField*>* fields=new vector<JObjectStreamField*>;
        for (int i = 0; i < clFields->size(); i++) {
            JField* f=clFields->at(i);
            if (true){//TODO !f->isStatic() && !f->isTransient()) {
                JObjectStreamField* ff=new JObjectStreamField(f,false,true);
                fields->push_back(ff);
            }
        }
        if (fields->size()==0){
            return NULL;
        }else{
            return &(fields->at(0));
        }
    }
    return NULL;
}

static JObjectStreamField** getSerialFields(JClass* cl){
    JObjectStreamField** fields=NULL;
    if (JSerializable::getClazz()->isAssignableFrom(cl) && !JExternalizable::getClazz()->isAssignableFrom(cl) &&
        !cl->isProxy() && !cl->isInterface()){
        fields = createFields(cl);
        //Arrays.sort(fields);
   }
   return fields;
}

JObjectStreamClass::JObjectStreamClass(JClass* _class):JObject(getClazz()){
    this->numFields=0;
    this->primDataSize = 0;
    this->numObjFields = 0;
    this->jClass=_class;
    this->name = _class->getName();
    this->bIsProxy=_class->isProxy();
    this->bIsEnum = _class->isEnum();
    this->serializable=JSerializable::getClazz()->isAssignableFrom(_class);
    this->externalizable=JExternalizable::getClazz()->isAssignableFrom(_class);

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

qint16 JObjectStreamClass::getNumFields(){
    return numFields;
}

qint32 JObjectStreamClass::getNumObjFields(){
    return numObjFields;
}

JObjectStreamField* JObjectStreamClass::getField(int i){
    if (fields == NULL) {
        throw new JInternalError("no fields!");
    }
    return fields[i];
}

const char* JObjectStreamClass::getName(){
    return name.c_str();
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

    qint8 flags = in->readByte();
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

    numFields = in->readShort();
    if (bIsEnum && numFields != 0) {
        stringstream ss;
        ss<<"enum "<<name<<" descriptor has non-zero field count: " << numFields;
        throw new JInvalidClassException(ss.str());
    }
    if (numFields > 0) {
        fields = new JObjectStreamField*[numFields];
        for (int i = 0; i < numFields; ++i) {
            char tcode=(char) in->readByte();;
            string fname=in->readUTF();
            string signature(&tcode);
            if ((tcode=='L' || (tcode=='['))){
                JString* readString=in->readTypeString();
                signature=readString->getString();//TODO detele object
            }
            fields[i]=new JObjectStreamField(fname,signature,false);
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
    numFields = model->numFields;
    fields = new JObjectStreamField*[numFields];
    for (int i = 0; i < numFields; ++i) {
        fields[i] = model->fields[i];
    }
    primDataSize = model->primDataSize;
    numObjFields = model->numObjFields;

    //TODO set externalizable by checking interface

    vector<JClass*> args;
    args.push_back(JObjectInputStream::getClazz());
    if (jClass->hasMethod("readObject",&args)){
        readObjectMethod = jClass->getMethod("readObject",&args);
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
    name = jClass->getName();

    //TODO should correct readObjectMethod for the proxy
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

void JObjectStreamClass::writeNonProxy(JObjectOutputStream* out){
    /*  TODO
        out.writeUTF(name);
        out.writeLong(getSerialVersionUID());

        byte flags = 0;
        if (externalizable) {
            flags |= ObjectStreamConstants.SC_EXTERNALIZABLE;
            int protocol = out.getProtocolVersion();
            if (protocol != ObjectStreamConstants.PROTOCOL_VERSION_1) {
                flags |= ObjectStreamConstants.SC_BLOCK_DATA;
            }
        } else if (serializable) {
            flags |= ObjectStreamConstants.SC_SERIALIZABLE;
        }
        if (hasWriteObjectData) {
            flags |= ObjectStreamConstants.SC_WRITE_METHOD;
        }
        if (isEnum) {
            flags |= ObjectStreamConstants.SC_ENUM;
        }
        out.writeByte(flags);

        out.writeShort(fields.length);
        for (int i = 0; i < fields.length; i++) {
            ObjectStreamField f = fields[i];
            out.writeByte(f.getTypeCode());
            out.writeUTF(f.getName());
            if (!f.isPrimitive()) {
                out.writeTypeString(f.getTypeString());
            }
        }
*/
}

JObject *JObjectStreamClass::newInstance() {
    return jClass->newInstance();
}

void JObjectStreamClass::computeFieldOffsets() {
    primDataSize = 0;
    numObjFields = 0;
    int firstObjIndex = -1;

    for (int i = 0; i < numFields; ++i) {
        switch (fields[i]->getTypeCode()) {
        case 'Z':
        case 'B':
            fields[i]->setOffset(primDataSize++);
            break;

        case 'C':
        case 'S':
            fields[i]->setOffset(primDataSize);
            primDataSize += 2;
            break;

        case 'I':
        case 'F':
            fields[i]->setOffset(primDataSize);
            primDataSize += 4;
            break;

        case 'J':
        case 'D':
            fields[i]->setOffset(primDataSize);
            primDataSize += 8;
            break;

        case '[':
        case 'L':
            fields[i]->setOffset(numObjFields++);
            if (firstObjIndex == -1) {
                firstObjIndex = i;
            }
            break;

        default:
            throw new JInternalError();
        }
    }
    if (firstObjIndex != -1 && firstObjIndex + numObjFields != numFields) {
        throw new JInvalidClassException(name+" : illegal field order");
    }
}

void JObjectStreamClass::setPrimFieldValues(JObject* obj, qint8 *buf) {
    int pos = 0;
    for (int i = 0; i < numFields-numObjFields; ++i) {
        JObjectStreamField* f = fields[i];
        switch (f->getTypeCode()) {
            case 'Z': {
                JPrimitiveBoolean* jPrimitiveBoolean=new JPrimitiveBoolean(JBits::getBool(buf,pos++));
                obj->getClass()->getField(f->getName())->set(obj,jPrimitiveBoolean);
                break;

            }case 'B':{
                JPrimitiveByte* jPrimitiveByte=new JPrimitiveByte((quint8) (buf[pos++]));
                obj->getClass()->getField(f->getName())->set(obj,jPrimitiveByte);
                break;

            }case 'C':{
                JPrimitiveChar* jPrimitiveChar=new JPrimitiveChar((char) (buf[pos+1]));
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

void JObjectStreamClass::getPrimFieldValues(JObject* obj,qint8* buf,JObjectOutputStream* out){
    if (obj==NULL){
        throw new JNullPointerException();
    }
    for (int i=0 ; i< numFields-numObjFields ; i++){//TODO check corret size
        JObjectStreamField* f=fields[i];
        JField* field=obj->getClass()->getField(f->getName());
        int off=f->getOffset();
        switch(f->getTypeCode()){
            case 'Z':{
                JPrimitiveBoolean* b=(JPrimitiveBoolean*)field->get(obj);
                bool v=b->get();
                out->writeBoolean(v);
                JBits::putBoolean(buf, off, v);
                break;

            }case 'B' :{
                JPrimitiveByte* b=(JPrimitiveByte*)field->get(obj);
                quint8 v=b->get();
                out->writeByte(v);
                buf[off] = v;
                break;

            }case 'C':{
                JPrimitiveChar* b=(JPrimitiveChar*)field->get(obj);
                quint16 v = b->get();
                out->writeChar(v);
                JBits::putChar(buf, off, v);
                break;

            } case 'S':{
                JPrimitiveShort* b =(JPrimitiveShort*)field->get(obj);
                qint16 v = b->get();
                out->writeShort(v);
                JBits::putShort(buf, off, v);
                break;

            }case 'I' :{
                JPrimitiveInt* b=(JPrimitiveInt*)field->get(obj);
                qint32 v = b->get();
                out->writeInt(v);
                JBits::putInt(buf, off, v);
                break;

            }case 'F' :{
                JPrimitiveFloat* b=(JPrimitiveFloat*)field->get(obj);
                float v = b->get();
                out->writeFloat(v);
                JBits::putFloat(buf, off, v);
                break;

            }case 'J': {
                JPrimitiveLong* b=(JPrimitiveLong*)field->get(obj);
                qint64 v = b->get();
                out->writeLong(v);
                JBits::putLong(buf, off, v);
                break;

            }case 'D': {
                JPrimitiveDouble* b=(JPrimitiveDouble*)field->get(obj);
                double v = b->get();
                out->writeDouble(v);
                JBits::putDouble(buf, off, v);
            }
        }
    }
}

void JObjectStreamClass::setObjectFieldValues(JObject* jObject,JObject** values) {
    for (int i = numFields - numObjFields; i < numFields; ++i) {
        JObject* current = values[i-numFields+numObjFields];
        jObject->getClass()->getField(fields[i]->getName())->set(jObject,current);
    }
}

vector<JObjectStreamClass*>* JObjectStreamClass::getClassDataLayout(){
    if(!hierarchy->empty()){
        hierarchy->clear();
    }
    JObjectStreamClass* copy = new JObjectStreamClass(*this);
    while(copy != NULL && copy->getJClass()!=JObject::getClazz() ){
        hierarchy->push_back(copy);
        copy = copy->getSuperDesc();
    }
    return hierarchy;
}

vector<JObjectStreamClass*>* JObjectStreamClass::getHierarchy(){
    return this->hierarchy;
}

string JObjectStreamClass::toString(){
    stringstream sstr;
    sstr<<"Class description :\nClass name : "<<name;
    sstr<<", SUID = "<<suid<<endl;
    sstr<<"Fields description :\nNumber of serializable fields = "<<numFields<<endl;
    for (int i = 0; i < numFields; ++i) {
        sstr<<"type code : "<<fields[i]->getTypeCode()<<", name : "<<fields[i]->getName()<<endl;
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
    //deleteVectorOfPointers(fields);
    //TODO deleteVectorOfPointers(hierarchy);
}
