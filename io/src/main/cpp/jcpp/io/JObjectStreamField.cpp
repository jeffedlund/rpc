#include "JObjectStreamField.h"
#include "JObjectStreamClass.h"
#include "JLang.h"

JObjectStreamField::JObjectStreamField(){
    this->type=NULL;
    this->unshared=false;
    this->field=NULL;
}

JObjectStreamField::JObjectStreamField(string name,JClass* type){
    this->name=name;
    this->type=type;
    this->unshared=false;
    this->signature=JObjectStreamClass::getClassSignature(type);
    this->field=NULL;
}

JObjectStreamField::JObjectStreamField(string name,JClass* type,bool unshared){
    this->name=name;
    this->type=type;
    this->unshared=unshared;
    this->signature=JObjectStreamClass::getClassSignature(type);
    this->field=NULL;
}

JObjectStreamField::JObjectStreamField(string name,string signature,bool unshared){
    this->name=name;
    this->signature=signature;
    this->unshared=unshared;
    this->field=NULL;
    switch(signature.at(0)){
        case 'Z':
            type = JPrimitiveBoolean::getClazz();
            break;
        case 'B':
            type = JPrimitiveByte::getClazz();
            break;
        case 'C':
            type = JPrimitiveChar::getClazz();
            break;
        case 'S':
            type = JPrimitiveShort::getClazz();
            break;
        case 'I':
            type = JPrimitiveInt::getClazz();
            break;
        case 'J':
            type = JPrimitiveLong::getClazz();
            break;
        case 'F':
            type = JPrimitiveFloat::getClazz();
            break;
        case 'D':
            type = JPrimitiveDouble::getClazz();
            break;
        case 'L':
        case '[':
            type = JObject::getClazz();
            break;
        default:
            throw new JIllegalArgumentException("illegal signature");
    }
}

JObjectStreamField::JObjectStreamField(JField* field,bool unshared,bool showType){
    this->field=field;
    this->unshared=unshared;
    this->name=field->getName();
    JClass* ftype=field->getType();
    type=(showType||ftype->isPrimitive()?ftype:JObject::getClazz());
    signature=JObjectStreamClass::getClassSignature(ftype);
}

string JObjectStreamField::getName(){
    return name;
}

JClass* JObjectStreamField::getType(){
    return type;
}

char JObjectStreamField::getTypeCode(){
    return signature.at(0);
}

string JObjectStreamField::getTypeString(){
    return isPrimitive()?"":signature;
}

qint32 JObjectStreamField::getOffset(){
    return offset;
}

void JObjectStreamField::setOffset(qint32 offset){
    this->offset=offset;
}

bool JObjectStreamField::isPrimitive(){
    char tcode=signature.at(0);
    return (tcode!='L') && (tcode!='[');
}

bool JObjectStreamField::isUnshared(){
    return unshared;
}

JField* JObjectStreamField::getField(){
    return field;
}

string JObjectStreamField::getSignature(){
    return signature;
}

JObjectStreamField::~JObjectStreamField(){
}
