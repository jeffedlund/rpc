#ifndef JFILENOTFOUNDEXCEPTION_H
#define JFILENOTFOUNDEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JFileNotFoundException : public JIOException  {
            public:
                static JClass* getClazz();
                JFileNotFoundException();
                virtual ~JFileNotFoundException();
        };
    }
}

#endif // JFILENOTFOUNDEXCEPTION_H
