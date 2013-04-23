#ifndef JCLOSEDFILESYSTEMEXCEPTION_H
#define JCLOSEDFILESYSTEMEXCEPTION_H

#include "JIllegalStateException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JClosedFileSystemException : public JIllegalStateException  {
                public:
                    static JClass* getClazz();
                    JClosedFileSystemException();
                    virtual ~JClosedFileSystemException();
            };
        }
    }
}

#endif // JCLOSEDFILESYSTEMEXCEPTION_H
