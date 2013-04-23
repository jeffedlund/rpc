#ifndef JREADONLYFILESYSTEMEXCEPTION_H
#define JREADONLYFILESYSTEMEXCEPTION_H

#include "JUnsupportedOperationException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JReadOnlyFileSystemException : public JUnsupportedOperationException  {
                public:
                    static JClass* getClazz();
                    JReadOnlyFileSystemException();
                    virtual ~JReadOnlyFileSystemException();
            };
        }
    }
}

#endif // JREADONLYFILESYSTEMEXCEPTION_H
