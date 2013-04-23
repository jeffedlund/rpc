#ifndef JDIRECTORYNOTEMPTYEXCEPTION_H
#define JDIRECTORYNOTEMPTYEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JDirectoryNotEmptyException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JDirectoryNotEmptyException();
                    JDirectoryNotEmptyException(string dir);
                    virtual ~JDirectoryNotEmptyException();

            };
        }
    }
}

#endif // JDIRECTORYNOTEMPTYEXCEPTION_H
