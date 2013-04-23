#ifndef JFILESYSTEMLOOPEXCEPTION_H
#define JFILESYSTEMLOOPEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemLoopException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JFileSystemLoopException();
                    JFileSystemLoopException(string msg);
                    virtual ~JFileSystemLoopException();
            };
        }
    }
}

#endif // JFILESYSTEMLOOPEXCEPTION_H
