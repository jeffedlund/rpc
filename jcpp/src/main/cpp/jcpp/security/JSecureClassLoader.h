#ifndef JSECURECLASSLOADER_H
#define JSECURECLASSLOADER_H

#include "JClassLoader.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace security{
        class JCPP_LIBRARY_EXPORT JSecureClassLoader : public JClassLoader{
            protected:
                JSecureClassLoader(JClass* _class,JClassLoader* parent);
            public:
                static JClass* getClazz();
                virtual ~JSecureClassLoader();
        };
    }
}

#endif // JSECURECLASSLOADER_H
