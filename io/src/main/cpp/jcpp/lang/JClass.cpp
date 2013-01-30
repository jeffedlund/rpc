#ifndef JCLASS_CPP
#define JCLASS_CPP

#include "JClass.h"
#include "JClassLoader.h"
#include "JMethod.h"
#include <QtGlobal>
using namespace std;

JClass* JClass::clazz=new JClass(JClassLoader::BOOT_CLASS_LOADER);

JClass::JClass(JClassLoader* classLoader):JObject(this){
    this->classLoader=classLoader;
    this->bIsArray=false;
    this->bIsProxy=false;
    this->bIsEnum=false;
    this->bIsInterface=false;
    this->bIsPrimitive=false;
}

JClass::JClass():JObject(this){
    this->classLoader=JClassLoader::BOOT_CLASS_LOADER;
    this->bIsArray=false;
    this->bIsProxy=false;
    this->bIsEnum=false;
    this->bIsInterface=false;
    this->bIsPrimitive=false;
}

void JClass::setName(string name){
    this->name=name;
    //name.find_last_of() TODO
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

vector<JObject*>* JClass::getEnumConstants(){
    return enumConstants;
}

JField* JClass::getField(string name){
    return fields->at(name);
}

vector<JField*>* JClass::getFields(){
    return NULL;//TODO
}

vector<JClass*>* JClass::getInterfaces(){
    return interfaces;
}

JMethod* JClass::getMethod(string name, vector<JClass*>* parameterTypes){
    return NULL;//TODO
}

vector<JMethod*>* JClass::getMethods(){
    return NULL;//TODO
}

JClass* JClass::getSuperclass(){
    return superClass;
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
    return false;//TODO
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

JObject* JClass::newInstance(){
    return NULL;//TODO
}

qint64 JClass::getSerialVersionUID(){
    return 1;//TODO
}

string JClass::toString(){
    return "[Class:"+name+"]";
}

JClass::~JClass(){
}

#endif // JCLASS_CPP
/*

TODO
string MArray::getArrayObjectName() const {
    string type = getComponentType();
    if(type.compare("qint32") == 0)
        return "[I";

    else if(type.compare("quint16") == 0)
        return "[C";

    else if(type.compare("double") == 0)
        return "[D";

    else if(type.compare("float") == 0)
        return "[F";

    else if(type.compare("qint16") == 0)
        return "[S";

    else if(type.compare("bool") == 0)
        return "[Z";

    else if(type.compare("qint64") == 0)
        return "[J";

    else if(type.compare("qint8") == 0)
        return "[B";

    else if(type.compare("MArray") == 0){
        return "[[";
    }

    else{
        type = type.substr(0, type.size() - 1);
        QString s(JavaMapper::mapper.value(type.c_str()));
        return s.replace('.', '/').toStdString().append(";").insert(0,"[L");
    }
}

*/
