#ifndef JDIRECTORYITERATOREXCEPTION_H
#define JDIRECTORYITERATOREXCEPTION_H

#include "JConcurrentModificationException.h"
#include "JThrowable.h"
#include "JIOException.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace nio{
        namespace file{
            class JDirectoryIteratorException : public JConcurrentModificationException  {
                public:
                    static JClass* getClazz();
                    JDirectoryIteratorException();
                    JDirectoryIteratorException(JIOException* cause);
                    virtual ~JDirectoryIteratorException();
            };
        }
    }
}

#endif // JDIRECTORYITERATOREXCEPTION_H
