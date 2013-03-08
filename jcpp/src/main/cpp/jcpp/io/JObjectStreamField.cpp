#include "JObjectStreamField.h"
#include "JObjectStreamClass.h"
#include "JLANG.h"
#include "Object.h"

namespace jcpp{
    namespace io{
        JObjectStreamField::JObjectStreamField(){
            this->type=NULL;
            this->unshared=false;
            this->field=NULL;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(string name,JClass* type){
            this->name=name;
            this->type=type;
            this->unshared=false;
            this->signature=type->getSignature();
            this->field=NULL;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(string name,JClass* type,bool unshared){
            this->name=name;
            this->type=type;
            this->unshared=unshared;
            this->signature=type->getSignature();
            this->field=NULL;
            setTypeString();
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
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JField* field,bool unshared,bool showType){
            this->field=field;
            this->unshared=unshared;
            this->name=field->getName();
            JClass* ftype=field->getType();
            type=(showType||ftype->isPrimitive()?ftype:JObject::getClazz());
            signature=ftype->getSignature();
            setTypeString();
        }

        string JObjectStreamField::getName(){
            return name;
        }

        JClass* JObjectStreamField::getType(){
            return type;
        }

        jchar JObjectStreamField::getTypeCode(){
            return (jchar)signature.at(0);
        }

        void JObjectStreamField::setTypeString(){
            typeString=new JString(isPrimitive()?"":signature);
        }

        JString* JObjectStreamField::getTypeString(){
            return typeString;
        }

        jint JObjectStreamField::getOffset(){
            return offset;
        }

        void JObjectStreamField::setOffset(jint offset){
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
            delete typeString;
        }
    }
}
