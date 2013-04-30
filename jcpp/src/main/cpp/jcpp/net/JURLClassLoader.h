#ifndef JURLCLASSLOADER_H
#define JURLCLASSLOADER_H

#include "JSecureClassLoader.h"
#include "JFile.h"

using namespace jcpp::security;
using namespace jcpp::io;

namespace jcpp{
    namespace net{
        class JCPP_LIBRARY_EXPORT JURLClassLoader : public JSecureClassLoader{
        protected:
            vector<JFile*>* files;
            void loadClasses();

        public:
            JURLClassLoader(vector<JFile*>* files,JClassLoader* parent);
            static JClass* getClazz();
            virtual ~JURLClassLoader();
        };
    }
}
#endif // JURLCLASSLOADER_H
