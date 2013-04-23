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
                    JNotLinkException(string file);
                    JNotLinkException(string file,string other,string reason);
                    virtual ~JNotLinkException();
            };
        }
    }
}

#endif // JNOTLINKEXCEPTION_H
