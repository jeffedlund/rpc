#ifndef JDEFAULTFILESYSTEM_H
#define JDEFAULTFILESYSTEM_H

#include "JIOFileSystem.h"
#include "JObject.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JDefaultFileSystem : public JObject  {
            public:
                static JClass* getClazz();
                static JFileSystem* getFileSystem();
                virtual ~JDefaultFileSystem();

        };
    }
}

#endif // JDEFAULTFILESYSTEM_H
