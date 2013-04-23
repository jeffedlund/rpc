#ifndef JFILESYSTEMNOTFOUNDEXCEPTION_H
#define JFILESYSTEMNOTFOUNDEXCEPTION_H

#include "JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemNotFoundException : public JRuntimeException  {
                public:
                    static JClass* getClazz();
                    JFileSystemNotFoundException();
                    JFileSystemNotFoundException(string msg);
                    virtual ~JFileSystemNotFoundException();
            };
        }
    }
}

#endif // JFILESYSTEMNOTFOUNDEXCEPTION_H
