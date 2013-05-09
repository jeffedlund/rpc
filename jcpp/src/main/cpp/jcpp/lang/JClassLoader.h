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
    //TODO getResource, getResources, findResource, findResources,
    //getSystemResource, getSystemResources, getResourceAsStream, getSystemResourceAsStream,
    //getSystemClassLoader, findLibrary
        class JCPP_LIBRARY_EXPORT JClassLoader : public JObject{
        private:
            JClassLoader(bool root);
        protected:
            JClassLoader* parent;
            map<JString, JClass*>* classes;
            bool bIsBootClassLoader;
            static JClass* getClazz(JClassLoader* classLoader);
            JClassLoader(JClass* _class,JClassLoader* parent);
            void initClasses(JPackage* p);

        public:
            static JClassLoader* getBootClassLoader();
            static void init();
            JClassLoader* getParent();
            jbool isBootClassLoader();
            void addClass(JClass* jClass);
            JClass* loadClass(JString name);
            JClass* loadClassBySignature(JString name);
            static JClass* getClazz();
            virtual ~JClassLoader();
        };
    }
}


#endif // JCLASSLOADER__H
