#ifndef JFILEALREADYEXISTSEXCEPTION_H
#define JFILEALREADYEXISTSEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileAlreadyExistsException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JFileAlreadyExistsException();
                    JFileAlreadyExistsException(string file);
                    JFileAlreadyExistsException(string file,string other,string reason);
                    virtual ~JFileAlreadyExistsException();
            };
        }
    }
}

#endif // JFILEALREADYEXISTSEXCEPTION_H
