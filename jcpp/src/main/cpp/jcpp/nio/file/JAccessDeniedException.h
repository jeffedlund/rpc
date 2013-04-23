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
                    JAccessDeniedException(string file);
                    JAccessDeniedException(string file,string other,string reason);
                    virtual ~JAccessDeniedException();
            };
        }
    }
}

#endif // JACCESSDENIEDEXCEPTION_H
