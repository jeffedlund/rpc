#include "JBootClassBuilder.h"
#include "JIO.h"
#include "JLang.h"
#include "JLangReflect.h"
#include "JUtil.h"

static JBootClassBuilder* bootClassBuilder;

JClassBuilder* JBootClassBuilder::getBootClassBuilder(){
    if (bootClassBuilder==NULL){
        bootClassBuilder=new JBootClassBuilder();
    }
    return bootClassBuilder;
}

JBootClassBuilder::JBootClassBuilder(){
    classes=new vector<JClass*>();
    for (int i=0;i<LANG_CLASSES_SIZE;i++){
        classes->push_back(LANG_CLASSES[i]);
    }
    for (int i=0;i<LANG_REFLECT_CLASSES_SIZE;i++){
        classes->push_back(LANG_REFLECT_CLASSES[i]);
    }
    for (int i=0;i<UTIL_CLASSES_SIZE;i++){
        classes->push_back(UTIL_CLASSES[i]);
    }
    for (int i=0;i<IO_CLASSES_SIZE;i++){
        classes->push_back(IO_CLASSES[i]);
    }
}

void JBootClassBuilder::addClass(JClass* clazz){
    classes->push_back(clazz);
}

vector<JClass*>* JBootClassBuilder::getClasses(){
    return classes;
}

