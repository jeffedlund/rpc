#ifndef JNOTLINKEXCEPTION_H
#define JNOTLINKEXCEPTION_H

#include "JFileSystemException.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JNotLinkException : public JFileSystemException  {
                public:
                    static JClass* getClazz();
                    JNotLinkException();
                    JNotLinkException(JString file);
                    JNotLinkException(JString file,JString other,JString reason);
                    virtual ~JNotLinkException();
            };
        }
    }
}

#endif // JNOTLINKEXCEPTION_H
