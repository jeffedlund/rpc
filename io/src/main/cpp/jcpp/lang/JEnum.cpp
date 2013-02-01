#include "JEnum.h"
#include "JClass.h"

JEnum::JEnum(JEnumClass* _class,string name,int ordinal):JObject(_class){
    this->name=name;
    this->ordinal=ordinal;
}

static JClass* clazz;

JClass* JEnum::getClazz(){
    if (clazz==NULL){
        clazz=new JEnumClass();
    }
    return clazz;
}

string JEnum::getName(){
    return name;
}

int JEnum::getOrdinal(){
    return ordinal;
}

string JEnum::toString(){
    return name;
}

JEnum::~JEnum() {
}
