#ifndef JATOMICMOVENOTSUPPORTEDEXCEPTION_H
#define JATOMICMOVENOTSUPPORTEDEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JAtomicMoveNotSupportedException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JAtomicMoveNotSupportedException();
                    JAtomicMoveNotSupportedException(string source,string target,string reason);
                    virtual ~JAtomicMoveNotSupportedException();
            };
        }
    }
}

#endif // JATOMICMOVENOTSUPPORTEDEXCEPTION_H
