#ifndef JNOTDIRECTORYEXCEPTION_H
#define JNOTDIRECTORYEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JNotDirectoryException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JNotDirectoryException();
                    JNotDirectoryException(JString file);
                    virtual ~JNotDirectoryException();
            };
        }
    }
}

#endif // JNOTDIRECTORYEXCEPTION_H
