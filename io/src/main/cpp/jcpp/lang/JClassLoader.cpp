#include "JClassLoader.h"

using namespace std;


JClassLoader* JClassLoader::BOOT_CLASS_LOADER=new JClassLoader();//TODO

JClassLoader::JClassLoader(){
}

void JClassLoader::addClassBuilder(string className,JClassBuilder jClassBuilder){
   classBuilders[className]=jClassBuilder;
}

JObject* JClassLoader::createObject(string string){
    return NULL;//TODO
}

JClassLoader::~JClassLoader() {
}



