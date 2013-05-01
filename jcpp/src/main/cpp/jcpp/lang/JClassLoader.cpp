#include "JClassLoader.h"
#include "Collections.h"
#include "JClassNotFoundException.h"
#include <algorithm>
#include "JIO.h"
#include "JLANG.h"
#include "JREFLECT.h"
#include "JUTIL.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JClassLoaderClass : public JClass{
          public:
            JClassLoaderClass():JClass(true){
                this->canonicalName="java.lang.ClassLoader";
                this->name="java.lang.ClassLoader";
                this->simpleName="ClassLoader";
            }

            JClassLoaderClass(JClassLoader* classLoader):JClass(true){
                this->canonicalName="java.lang.ClassLoader";
                this->name="java.lang.ClassLoader";
                this->simpleName="ClassLoader";
                this->classLoader=classLoader;
            }

            JClassLoader* getClassLoader(){
                if (classLoader==NULL){
                    return JClassLoader::getBootClassLoader();
                }else{
                    return classLoader;
                }
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JClassLoader::getClazz(){
            if (clazz==NULL){
                clazz=new JClassLoaderClass();
            }
            return clazz;
        }

        JClass* JClassLoader::getClazz(JClassLoader* classLoader){
            if (clazz==NULL){
                clazz=new JClassLoaderClass(classLoader);
            }
            return clazz;
        }


        static JClassLoader* bootClassLoader;

        JClassLoader* JClassLoader::getBootClassLoader(){
            if (bootClassLoader==NULL){
                bootClassLoader=new JClassLoader(true);
            }
            return bootClassLoader;
        }

        static jbool initialized=false;
        void JClassLoader::init(){
            if (!initialized){
                initialized=true;
                getBootClassLoader()->initClasses(JCPP_PACKAGE::getPackage());
            }
        }

        JClassLoader::JClassLoader(JClass* _class,JClassLoader* parent):JObject(_class){
            this->classes=new map<string,JClass*>();
            this->bIsBootClassLoader=false;
            this->parent=(parent!=NULL ? parent : getBootClassLoader());
        }

        JClassLoader::JClassLoader(bool root):JObject(true){
            this->classes=new map<string,JClass*>();
            this->_class=getClazz(this);
            this->bIsBootClassLoader=root;
            this->parent=NULL;
        }

        bool JClassLoader::isBootClassLoader(){
            return bIsBootClassLoader;
        }

        void JClassLoader::addClass(JClass* jClass){
            JClass* tmp=getFromMap(classes,jClass->getName());
            if (tmp!=NULL && tmp!=jClass){
                throw new JIllegalArgumentException("class "+jClass->toString()+" already defined in classlaoder "+toString());
            }
            classes->insert(pair<string,JClass*>(jClass->getName(),jClass));
            jClass->classLoader=this;
        }

        void JClassLoader::initClasses(JPackage* p){
            for (unsigned int i=0;i<p->getClasses()->size();i++){
                JClass* c=p->getClasses()->at(i);
                addClass(c);
                vector<JClass*>* dc=c->getDeclaredClasses();
                for (unsigned int j=0;j<dc->size();j++){
                    addClass(dc->at(j));
                }
            }
            for (unsigned int i=0;i<p->getPackages()->size();i++){
                initClasses(p->getPackages()->at(i));
            }
        }

        JClass* JClassLoader::loadClass(string name){
            if (name.at(0)=='['){
                return loadClassBySignature(name);
            }
            JClass* jClass=NULL;
            if (!bIsBootClassLoader){
                if (parent!=NULL){
                    try{
                        jClass=parent->loadClass(name);
                    }catch(JClassNotFoundException* e1){
                    }
                }else{
                    try{
                        jClass=getBootClassLoader()->loadClass(name);
                    }catch(JClassNotFoundException* e1){
                    }
                }
            }
            if (jClass==NULL){
                jClass=getFromMap(classes,name);
                if (jClass==NULL){
                    throw new JClassNotFoundException("class "+name+" not found");
                }
            }
            return jClass;
        }

        JClass* JClassLoader::loadClassBySignature(string name){
            if (name.at(0)=='['){
                int nbArray=0;
                string classname;
                for (unsigned int i=0;i<name.size();i++){
                    if (name.at(i)=='['){
                        nbArray++;
                    }else{
                        classname=name.substr(i,name.size());
                        break;
                    }
                }
                JClass* componentClass;
                if (classname=="I"){
                    componentClass= JPrimitiveInt::getClazz();
                }else if (classname=="B"){
                    componentClass= JPrimitiveByte::getClazz();
                }else if (classname=="J"){
                    componentClass= JPrimitiveLong::getClazz();
                }else if (classname=="F"){
                    componentClass= JPrimitiveFloat::getClazz();
                }else if (classname=="D"){
                    componentClass= JPrimitiveDouble::getClazz();
                }else if (classname=="S"){
                    componentClass= JPrimitiveShort::getClazz();
                }else if (classname=="C"){
                    componentClass= JPrimitiveChar::getClazz();
                }else if (classname=="Z"){
                    componentClass= JPrimitiveBoolean::getClazz();
                }else if (classname=="V"){
                    componentClass= JVoid::getClazz();
                }else if (classname.at(0)=='L'){
                    classname=classname.substr(1,classname.size()-2);//remove ;
                    replace(classname.begin(),classname.end(),'/','.');
                    componentClass=loadClass(classname);
                }else{
                    throw new JInternalError();
                }
                JClass* current=componentClass;
                for (int i=0;i<nbArray;i++){
                    current=JPrimitiveArray::getClazz(current);
                }
                return current;
            }
            throw new JInternalError();
        }

        JClassLoader::~JClassLoader() {
            deleteMapOfValuePointer(classes);
        }
    }
}
