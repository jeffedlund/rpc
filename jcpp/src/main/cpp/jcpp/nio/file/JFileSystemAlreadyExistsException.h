#ifndef JFILESYSTEMALREADYEXISTSEXCEPTION_H
#define JFILESYSTEMALREADYEXISTSEXCEPTION_H

#include "JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemAlreadyExistsException : public JRuntimeException  {
                public:
                    static JClass* getClazz();
                    JFileSystemAlreadyExistsException();
                    JFileSystemAlreadyExistsException(JString msg);
                    virtual ~JFileSystemAlreadyExistsException();
            };
        }
    }
}

#endif // JFILESYSTEMALREADYEXISTSEXCEPTION_H
