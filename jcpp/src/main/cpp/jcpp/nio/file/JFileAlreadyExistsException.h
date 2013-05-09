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
                    JFileAlreadyExistsException(JString file);
                    JFileAlreadyExistsException(JString file,JString other,JString reason);
                    virtual ~JFileAlreadyExistsException();
            };
        }
    }
}

#endif // JFILEALREADYEXISTSEXCEPTION_H
