#ifndef JNOSUCHFILEEXCEPTION_H
#define JNOSUCHFILEEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JNoSuchFileException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JNoSuchFileException();
                    JNoSuchFileException(string file);
                    JNoSuchFileException(string file,string other,string reason);
                    virtual ~JNoSuchFileException();
            };
        }
    }
}

#endif // JNOSUCHFILEEXCEPTION_H
