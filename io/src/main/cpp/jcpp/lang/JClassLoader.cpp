#include "JClassLoader.h"
#include "Collections.h"
#include "JClassNotFoundException.h"

using namespace std;


static JClassLoader* bootClassLoader;

//implement a tree of classloaders ...
JClassLoader* JClassLoader::getBootClassLoader(){
    if (bootClassLoader==NULL){
        bootClassLoader=new JClassLoader();
    }
    return bootClassLoader;
}

JClassLoader::JClassLoader(){
    classes=new map<string,JClass*>();
}

void JClassLoader::addClasses(JClassBuilder* jClassBuilder){
    vector<JClass*>* c=jClassBuilder->getClasses();
    for (int i=0;i<c->size();i++){
        JClass* jClass=c->at(i);
        classes->insert(pair<string,JClass*>(jClass->getName(),jClass));
    }
}

JClass* JClassLoader::loadClass(string name){
    JClass* jClass=classes->at(name);
    if (jClass==NULL){
        throw new JClassNotFoundException("class "+name+" not found");
    }
    return jClass;
}

JClassLoader::~JClassLoader() {
    deleteMapOfValuePointer(classes);
}



