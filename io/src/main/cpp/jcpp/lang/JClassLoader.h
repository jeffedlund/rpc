#ifndef JCLASSLOADER_H
#define JCLASSLOADER_H

#include "JClassBuilder.h"
#include <map>
using namespace std;

namespace jcpp{
    namespace lang{
        class JClassLoader : public JObject{
        protected:
            map<string, JClass*>* classes;
            bool bIsBootClassLoader;
            bool bInitialized;
            static JClass* getClazz(JClassLoader* classLoader);
            JClassLoader(bool root);

            void initClasses();

        public:
            JClassLoader();

            static JClassLoader* getBootClassLoader();

            bool isBootClassLoader();

            void addClass(JClass* jClass);

            JClass* loadClass(string string);

            static JClass* getClazz();

            ~JClassLoader();
        };
    }
}


#endif // JCLASSLOADER__H
