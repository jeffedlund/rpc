#ifndef JCLASSLOADER_H
#define JCLASSLOADER_H

#include <map>
#include "JObject.h"
#include "JPackage.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
    //TODO implement tree of classloader,getResource, getResources, findResource, findResources,
    //getSystemResource, getSystemResources, getResourceAsStream, getSystemResourceAsStream,
    //getParent, getSystemClassLoader, findLibrary
        class JCPP_LIBRARY_EXPORT JClassLoader : public JObject{
        protected:
            map<string, JClass*>* classes;
            bool bIsBootClassLoader;
            bool bInitialized;
            static JClass* getClazz(JClassLoader* classLoader);
            JClassLoader(bool root);
            void initClasses();
            void initClasses(JPackage* p);

        public:
            JClassLoader();
            static JClassLoader* getBootClassLoader();
            bool isBootClassLoader();
            void addClass(JClass* jClass);
            JClass* loadClass(string string);
            //TODO test cases for this method
            JClass* loadClassBySignature(string name);
            static JClass* getClazz();
            virtual ~JClassLoader();
        };
    }
}


#endif // JCLASSLOADER__H
