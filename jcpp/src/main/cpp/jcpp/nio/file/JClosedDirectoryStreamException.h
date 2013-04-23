#ifndef JCLOSEDDIRECTORYSTREAMEXCEPTION_H
#define JCLOSEDDIRECTORYSTREAMEXCEPTION_H

#include "JIllegalStateException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JClosedDirectoryStreamException : public JIllegalStateException  {
                public:
                    static JClass* getClazz();
                    JClosedDirectoryStreamException();
                    virtual ~JClosedDirectoryStreamException();
            };
        }
    }
}

#endif // JCLOSEDDIRECTORYSTREAMEXCEPTION_H
