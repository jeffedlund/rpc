#include "JObjectStreamField.h"
#include "JObjectStreamClass.h"
#include "JLANG.h"
#include "Object.h"

namespace jcpp{
    namespace io{
        class JObjectStreamFieldClass : public JClass{
        public:
            JObjectStreamFieldClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectStreamField";
                name="java.io.ObjectStreamField";
                simpleName="ObjectStreamField";
                addInterface(JComparable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JObjectStreamField();
            }
        };

        static JClass* clazz;

        JClass* JObjectStreamField::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectStreamFieldClass();
            }
            return clazz;
        }

        JObjectStreamField::JObjectStreamField():JObject(getClazz()){
            this->type=NULL;
            this->unshared=false;
            this->field=NULL;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JString name,JClass* type):JObject(getClazz()){
            this->name=name;
            this->type=type;
            this->unshared=false;
            this->signature=type->getSignature();
            this->field=NULL;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JString name,JClass* type,jbool unshared):JObject(getClazz()){
            this->name=name;
            this->type=type;
            this->unshared=unshared;
            this->signature=type->getSignature();
            this->field=NULL;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JString name,JString signature,jbool unshared):JObject(getClazz()){
            this->name=name;
            this->signature=signature;
            this->unshared=unshared;
            this->field=NULL;
            switch(signature.charAt(0)){
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

        JObjectStreamField::JObjectStreamField(JField* field,jbool unshared,jbool showType):JObject(getClazz()){
            this->field=field;
            this->unshared=unshared;
            this->name=field->getName();
            JClass* ftype=field->getType();
            type=(showType||ftype->isPrimitive()?ftype:JObject::getClazz());
            signature=ftype->getSignature();
            setTypeString();
        }

        JString JObjectStreamField::getName(){
            return name;
        }

        JClass* JObjectStreamField::getType(){
            return type;
        }

        jchar JObjectStreamField::getTypeCode(){
            return (jchar)signature.charAt(0);
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

        jbool JObjectStreamField::isPrimitive(){
            jchar tcode=(jchar)signature.charAt(0);
            return (tcode!='L') && (tcode!='[');
        }

        jbool JObjectStreamField::isUnshared(){
            return unshared;
        }

        JField* JObjectStreamField::getField(){
            return field;
        }

        JString JObjectStreamField::getSignature(){
            return signature;
        }

        jint JObjectStreamField::compareTo(JObject* o){
            JObjectStreamField* other=dynamic_cast<JObjectStreamField*>(o);
            jbool isPrim = getType()->isPrimitive();
            if (isPrim != other->getType()->isPrimitive()) {
                return isPrim ? -1 : 1;
            }
            return JString::compare(getName(),other->getName());
        }

        JObjectStreamField::~JObjectStreamField(){
            delete typeString;
        }
    }
}
