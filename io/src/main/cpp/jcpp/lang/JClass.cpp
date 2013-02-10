#ifndef JCLASS_CPP
#define JCLASS_CPP

#include "JClass.h"
#include "JClassLoader.h"
#include "JMethod.h"
#include "JEnum.h"
#include <QtGlobal>
#include "Collections.h"
#include "JNoSuchFieldException.h"
#include "JNoSuchMethodException.h"
#include "JIllegalArgumentException.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveShort.h"
#include "JVoid.h"
#include <sstream>
#include "JInternalError.h"
#include <algorithm>
using namespace std;

class JClassClass : public JClass{
    public:
    JClassClass():JClass(true){
        this->canonicalName="java.lang.Class";
        this->name="java.lang.Class";
        this->simpleName="Class";
        this->serialVersionUID=3206093459760846163;
    }

    JClassLoader* getClassLoader(){
        return JClassLoader::getBootClassLoader();
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return this;//returning itself, bof ...
    }

};

static JClass* clazz;

JClass* JClass::getClazz(){
    if (clazz==NULL){
        clazz=new JClassClass();
    }
    return clazz;
}

string JClass::getClassSignature(JClass* _class){
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
        } else if (_class == JVoid::getClazz()) {
            ss<<'V';
        } else {
            throw new JInternalError();
        }
    }else{
        string name=_class->getName();
        string newName(name);
        replace(newName.begin(),newName.end(),'/','.');
        ss<<'L'<<newName<<";";
    }
    return ss.str();
}

JClass::JClass(JClassLoader* classLoader):JObject(JClass::getClazz()){
    this->classLoader=classLoader;
    this->bIsArray=false;
    this->bIsProxy=false;
    this->bIsEnum=false;
    this->bIsInterface=false;
    this->bIsPrimitive=false;
    this->enumConstants=new vector<JEnum*>;
    this->fields=new map<string,JField*>;
    this->fieldsList=new vector<JField*>;
    this->methods=new map<string,JMethod*>;
    this->methodsList=new vector<JMethod*>;
    this->interfaces=new vector<JClass*>;
}

JClass::JClass():JObject(JClass::getClazz()){
    this->classLoader=JClassLoader::getBootClassLoader();
    this->bIsArray=false;
    this->bIsProxy=false;
    this->bIsEnum=false;
    this->bIsInterface=false;
    this->bIsPrimitive=false;
    this->enumConstants=new vector<JEnum*>;
    this->fields=new map<string,JField*>;
    this->fieldsList=new vector<JField*>;
    this->methods=new map<string,JMethod*>;
    this->methodsList=new vector<JMethod*>;
    this->interfaces=new vector<JClass*>;
}

JClass::JClass(bool root):JObject(root){
    this->bIsArray=false;
    this->bIsProxy=false;
    this->bIsEnum=false;
    this->bIsInterface=false;
    this->bIsPrimitive=false;
    this->enumConstants=new vector<JEnum*>;
    this->fields=new map<string,JField*>;
    this->fieldsList=new vector<JField*>;
    this->methods=new map<string,JMethod*>;
    this->methodsList=new vector<JMethod*>;
    this->interfaces=new vector<JClass*>;
}

string JClass::getCanonicalName(){
    return canonicalName;
}

string JClass::getName(){
    return name;
}

string JClass::getSimpleName(){
    return simpleName;
}

JClassLoader* JClass::getClassLoader(){
    return classLoader;
}

JClass* JClass::getComponentType(){
    return componentType;
}

vector<JEnum*>* JClass::getEnumConstants(){
    return enumConstants;
}

JEnum* JClass::valueOf(string value){
    for (int i=0;i<enumConstants->size();i++){
        JEnum* e=enumConstants->at(i);
        if (e->getName()->getString()==value){
            return e;
        }
    }
    throw new JIllegalArgumentException("No enum constant "+value+" in enum "+getName());
}

JField* JClass::getField(string name){
    JField* field=getFromMap(fields,name);
    if (field==NULL){
        throw JNoSuchFieldException("field "+name+" not delared in "+getName());
    }
    return field;
}

vector<JField*>* JClass::getFields(){
    return fieldsList;
}

vector<JClass*>* JClass::getInterfaces(){
    return interfaces;
}

bool JClass::hasMethod(string name, vector<JClass*>* parameterTypes){
    JMethod* method=getFromMap(methods,name);
    if (method==NULL){
        return false;
    }
    return true;
}

JMethod* JClass::getMethod(string name, vector<JClass*>* parameterTypes){
    JMethod* method=getFromMap(methods,name);
    if (method==NULL){
        throw JNoSuchMethodException("method "+name+" not declared in "+getName());//we should check using signature ...
    }
    return method;
}

vector<JMethod*>* JClass::getMethods(){
    return methodsList;
}

void JClass::addEnumConstant(JEnum* enumConstant){
    enumConstants->push_back(enumConstant);
}

void JClass::addField(JField* field){
    fieldsList->push_back(field);
    fields->insert(pair<string,JField*>(field->getName(),field));//TODO use better map container
}

void JClass::addMethod(JMethod* method){
    methodsList->push_back(method);
    methods->insert(pair<string,JMethod*>(method->getName(),method));
}

void JClass::addInterface(JClass* interface){
    interfaces->push_back(interface);
}

bool JClass::isArray(){
    return bIsArray;
}

bool JClass::isProxy(){
    return bIsProxy;
}

bool JClass::isEnum(){
    return bIsEnum;
}

bool JClass::isAssignableFrom(JClass* clazz){
    JClass* current=clazz;
    while (current!=NULL){
        if (current==this){
            return true;
        }
        for (int i=0;i<current->getInterfaces()->size();i++){
             JClass* interf=current->getInterfaces()->at(i);
             if (this==interf){
                return true;
             }
        }
        current=current->getSuperclass();//check also interfaces
    }
    return false;
}

bool JClass::isInstance(JObject* object){
    return object->getClass()==this;
}

bool JClass::isInterface(){
    return bIsInterface;
}

bool JClass::isPrimitive(){
    return bIsPrimitive;
}

qint64 JClass::getSerialVersionUID(){
    return serialVersionUID;
}

string JClass::toString(){
    return (isInterface()?"interface ":(isPrimitive()?"":"class "))+getName();
}

JClass::~JClass(){
    deleteVectorOfPointers(this->enumConstants);
    deleteVectorOfPointers(this->interfaces);
    deleteMapOfValuePointer(fields);
    deleteVectorOfPointers(fieldsList);
    deleteMapOfValuePointer(methods);
    deleteVectorOfPointers(methodsList);
}

#endif // JCLASS_CPP
