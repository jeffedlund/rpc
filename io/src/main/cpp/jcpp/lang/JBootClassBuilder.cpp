#include "JBootClassBuilder.h"
#include "JIO.h"
#include "JLang.h"
#include "JLangReflect.h"
#include "JUtil.h"

JBootClassBuilder::JBootClassBuilder(){
    classes=new vector<JClass*>();
    for (int i=0;i<LANG_CLASSES_SIZE;i++){
        classes->push_back(LANG_CLASSES[i]);
    }
    for (int i=0;i<LANG_REFLECT_CLASSES_SIZE;i++){
        classes->push_back(LANG_REFLECT_CLASSES[i]);
    }
    for (int i=0;i<UTL_CLASSES_SIZE;i++){
        classes->push_back(UTIL_CLASSES[i]);
    }
}

void JBootClassBuilder::addClass(JClass* clazz){
    classes->push_back(clazz);
}

vector<JClass*>* JBootClassBuilder::getClasses(){
    return classes;
}

