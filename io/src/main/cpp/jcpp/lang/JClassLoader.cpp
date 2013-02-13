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

        JClass* JClassLoader::getClazz(JClassLoader* classLoader){
            if (clazz==NULL){
                clazz=new JClassLoaderClass(classLoader);
            }
            return clazz;
        }


        static JClassLoader* bootClassLoader;

        //implement a tree of classloaders ...
        JClassLoader* JClassLoader::getBootClassLoader(){
            if (bootClassLoader==NULL){
                bootClassLoader=new JClassLoader(true);
            }
            return bootClassLoader;
        }

        JClassLoader::JClassLoader():JObject(true){
            this->classes=new map<string,JClass*>();
            this->_class=getClazz(this);
            this->bIsBootClassLoader=false;
            this->bInitialized=false;
        }

        JClassLoader::JClassLoader(bool root):JObject(true){
            this->classes=new map<string,JClass*>();
            this->_class=getClazz(this);
            this->bIsBootClassLoader=root;
            this->bInitialized=false;
        }

        bool JClassLoader::isBootClassLoader(){
            return bIsBootClassLoader;
        }

        void JClassLoader::addClass(JClass* jClass){
            classes->insert(pair<string,JClass*>(jClass->getName(),jClass));
        }

        void JClassLoader::initClasses(){
            if (!bInitialized){
                for (unsigned int i=0;i<JLANG::getPackage()->getClasses()->size();i++){
                    addClass(JLANG::getPackage()->getClasses()->at(i));
                }
                for (unsigned int i=0;i<JREFLECT::getPackage()->getClasses()->size();i++){
                    addClass(JREFLECT::getPackage()->getClasses()->at(i));
                }
                for (unsigned int i=0;i<JUTIL::getPackage()->getClasses()->size();i++){
                    addClass(JUTIL::getPackage()->getClasses()->at(i));
                }
                for (unsigned int i=0;i<JIO::getPackage()->getClasses()->size();i++){
                    addClass(JIO::getPackage()->getClasses()->at(i));
                }
                bInitialized=true;
            }
        }

        JClass* JClassLoader::loadClass(string name){
            if (bIsBootClassLoader){
                initClasses();
            }
            if (name.at(0)=='['){
                return JPrimitiveArray::loadClassBySignature(this,name);
            }
            JClass* jClass=getFromMap(classes,name);
            if (jClass==NULL){
                throw new JClassNotFoundException("class "+name+" not found");
            }
            return jClass;
        }

        JClassLoader::~JClassLoader() {
            deleteMapOfValuePointer(classes);
        }
    }
}
