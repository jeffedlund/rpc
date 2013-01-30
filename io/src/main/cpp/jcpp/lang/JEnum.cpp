#include "JEnum.h"
#include "JClass.h"

JEnumClass::JEnumClass():JClass(){
    this->enums=new vector<JEnum*>;
    this->bIsEnum=true;
}

JEnum* JEnumClass::valueOf(string value){
    return NULL;//TODO
}

JEnum::JEnum(JEnumClass* enumClass,string name,int ordinal):JObject(enumClass){
    this->name=name;
    this->ordinal=ordinal;
}

string JEnum::getName(){
    return name;
}

int JEnum::getOrdinal(){
    return ordinal;
}

JEnum::~JEnum() {
}
