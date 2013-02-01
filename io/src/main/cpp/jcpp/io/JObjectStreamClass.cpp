#include "JObjectStreamClass.h"
#include "JObjectStreamConstants.h"
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
#include "JBits.h"
#include <sstream>

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

JObjectStreamClass::JObjectStreamClass():JObject(getClazz()){
    this->name="";
    this->suid=-1;
    this->isProxy=false;
    this->isEnum=false;
    this->serializable=false;
    this->externalizable=false;
    this->writeObjectData=false;
    this->blockExternalData=true;
    this->numFields=0;
    this->primDataSize=0;
    this->numObjFields=0;
    this->fields = NULL;
}

bool JObjectStreamClass::hasReadObjectMethod() {
    return writeObjectData;
}

bool JObjectStreamClass::hasWriteObjectData() {
    return writeObjectData;
}

JClass* JObjectStreamClass::getJClass() const {
    return jClass;
}

qint16 JObjectStreamClass::getNumFields() const {
    return numFields;
}

qint32 JObjectStreamClass::getNumObjFields() const {
    return numObjFields;
}

JObjectStreamClass::Field JObjectStreamClass::getField(int i) const {
    if (fields == NULL) {
        throw "no fields!";
    }
    return fields[i];
}

const char *JObjectStreamClass::getName() const {
    return name.c_str();
}

int JObjectStreamClass::getPrimDataSize() const {
    return primDataSize;
}

JObjectStreamClass *JObjectStreamClass::getSuperDesc() const{
    return superDesc;
}

void JObjectStreamClass::readNonProxy(JObjectInputStream *in) {
    name = in->readUTF();
    suid = in->readLong();
    isProxy = false;

    qint8 flags = in->readByte();
    writeObjectData = ((flags & JObjectStreamConstants::SC_WRITE_METHOD) != 0);
    blockExternalData = ((flags & JObjectStreamConstants::SC_BLOCK_DATA) != 0);
    externalizable = ((flags & JObjectStreamConstants::SC_EXTERNALIZABLE) != 0);
    bool sflag = ((flags & JObjectStreamConstants::SC_SERIALIZABLE) != 0);
    if (externalizable && sflag) {
        throw "new InvalidClassException(name, \"serializable and externalizable flags conflict\")";//TODO
    }
    isEnum = ((flags & JObjectStreamConstants::SC_ENUM) != 0);
    serializable = externalizable || sflag;
    if (isEnum && suid != 0) {
        throw "new InvalidClassException(name, \"enum descriptor has non-zero serialVersionUID: \" + suid)";//TODO
    }

    numFields = in->readShort();
    if (isEnum && numFields != 0) {
        throw "new InvalidClassException(name, \"enum descriptor has non-zero field count: \" + numFields)";//TODO
    }
    if (numFields > 0) {
        fields = new Field[numFields];
        for (int i = 0; i < numFields; ++i) {
            fields[i].type = (char) in->readByte();
            fields[i].name =  in->readUTF();
            if (fields[i].type == 'L' || fields[i].type == '[') {
                in->readTypeString();//consume type string
            }
        }
    }
    computeFieldOffsets();
}

void JObjectStreamClass::initNonProxy(JObjectStreamClass * const model,JClass* jClass,JObjectStreamClass* superDesc){
    this->jClass = jClass;
    this->superDesc = superDesc;
    name = model->name;
    suid = model->suid;
    isProxy = false;
    isEnum = model->isEnum;
    serializable = model->serializable;
    externalizable = model->externalizable;
    blockExternalData= model->blockExternalData;
    writeObjectData = model->writeObjectData;
    numFields = model->numFields;
    fields = new Field[numFields];
    for (int i = 0; i < numFields; ++i) {
        fields[i] = model->fields[i];
    }
    primDataSize = model->primDataSize;
    numObjFields = model->numObjFields;
}

void JObjectStreamClass::initProxy(JClass* jClass,JObjectStreamClass* superDesc) {
    this->jClass= jClass;
    this->superDesc = superDesc;
    isProxy = true;
    serializable = true;
    suid = 0;
    fields = NULL;
    name = jClass->getName();
}

JObject *JObjectStreamClass::newInstance() {
    return jClass->newInstance();
}

void JObjectStreamClass::computeFieldOffsets() {
    primDataSize = 0;
    numObjFields = 0;
    int firstObjIndex = -1;

    for (int i = 0; i < numFields; ++i) {
        switch (fields[i].type) {
        case 'Z':
        case 'B':
            fields[i].offset = primDataSize++;
            break;

        case 'C':
        case 'S':
            fields[i].offset = primDataSize;
            primDataSize += 2;
            break;

        case 'I':
        case 'F':
            fields[i].offset =  primDataSize;
            primDataSize += 4;
            break;

        case 'J':
        case 'D':
            fields[i].offset = primDataSize;
            primDataSize += 8;
            break;

        case '[':
        case 'L':
            fields[i].offset = numObjFields++;
            if (firstObjIndex == -1) {
                firstObjIndex = i;
            }
            break;

        default:
            throw "new InternalError()";//TODO
        }
    }
    if (firstObjIndex != -1 && firstObjIndex + numObjFields != numFields) {
        throw "new InvalidClassException(name, \"illegal field order \")";//TODO
    }
}

void JObjectStreamClass::setPrimFieldValues(JObject* obj, qint8 *buf) {
    int pos = 0;
    for (int i = 0; i < numFields-numObjFields; ++i) {
        Field f = fields[i];
        switch (f.type) {
            case 'Z': {
                JPrimitiveBoolean* jPrimitiveBoolean=new JPrimitiveBoolean(JBits::getBool(buf,pos++));
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveBoolean);
                break;

            }case 'B':{
                JPrimitiveByte* jPrimitiveByte=new JPrimitiveByte((quint8) (buf[pos++]));
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveByte);
                break;

            }case 'C':{
                JPrimitiveChar* jPrimitiveChar=new JPrimitiveChar((char) (buf[pos+1]));
                pos += 2;
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveChar);
                break;

            }case 'S':{
                JPrimitiveShort* jPrimitiveShort=new JPrimitiveShort(JBits::getShort(buf,pos));
                pos += 2;
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveShort);
                break;

            }case 'I':{
                JPrimitiveInt* jPrimitiveInt=new JPrimitiveInt(JBits::getInt(buf,pos));
                pos += 4;
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveInt);
                break;

            }case 'F':{
                JPrimitiveFloat* jPrimitiveFloat=new JPrimitiveFloat(JBits::getFloat(buf,pos));
                pos += 4;
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveFloat);
                break;

            }case 'J':{
                JPrimitiveLong* jPrimitiveLong=new JPrimitiveLong(JBits::getLong(buf,pos));
                pos += 8;
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveLong);
                break;

            }case 'D':{
                JPrimitiveDouble* jPrimitiveDouble=new JPrimitiveDouble(JBits::getDouble(buf,pos));
                pos += 8;
                obj->getClass()->getField(f.name)->set(obj,jPrimitiveDouble);
                break;

            }default:{
                throw "setPrimFieldValue: invalid type code";//TODO
            }
        }
    }
}

void JObjectStreamClass::setObjectFieldValues(JObject* jObject,JObject** values) {
    for (int i = numFields - numObjFields; i < numFields; ++i) {
        JObject* current = values[i-numFields+numObjFields];
        jObject->getClass()->getField(fields[i].name)->set(jObject,current);
    }
}

string JObjectStreamClass::toString() const {
    stringstream sstr;
    sstr<<"Class description :\nClass name : "<<name;
    sstr<<", SUID = "<<suid<<endl;
    sstr<<"Fields description :\nNumber of serializable fields = "<<numFields<<endl;
    for (int i = 0; i < numFields; ++i) {
        sstr<<"type code : "<<fields[i].type<<", name : "<<fields[i].name<<endl;
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
    delete[] fields;
}
