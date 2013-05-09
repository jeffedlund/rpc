#ifndef JACCESSDENIEDEXCEPTION_H
#define JACCESSDENIEDEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JAccessDeniedException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JAccessDeniedException();
                    JAccessDeniedException(JString file);
                    JAccessDeniedException(JString file,JString other,JString reason);
                    virtual ~JAccessDeniedException();
            };
        }
    }
}

#endif // JACCESSDENIEDEXCEPTION_H
