#include "JClassLoader.h"
#include "Collections.h"
#include "JClassNotFoundException.h"

using namespace std;

class JClassLoaderClass : public JClass{
  public:
    JClassLoaderClass(){
        this->canonicalName="java.lang.ClassLoader";
        this->name="java.lang.ClassLoader";
        this->simpleName="ClassLoader";
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JClassLoader();
    }
};

static JClass* clazz;

JClass* JClassLoader::getClazz(){
    if (clazz==NULL){
        clazz=new JClassLoaderClass();
    }
    return clazz;
}


static JClassLoader* bootClassLoader;

//implement a tree of classloaders ...
JClassLoader* JClassLoader::getBootClassLoader(){
    if (bootClassLoader==NULL){
        bootClassLoader=new JClassLoader();
    }
    return bootClassLoader;
}

JClassLoader::JClassLoader():JObject(getClazz()){
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
