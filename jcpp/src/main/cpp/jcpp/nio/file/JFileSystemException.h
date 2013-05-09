#ifndef JFILESYSTEMEXCEPTION_H
#define JFILESYSTEMEXCEPTION_H

#include "JIOException.h"
#include "JString.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemException : public JIOException  {
                protected:
                    JString* file;
                    JString* other;
                    friend class JFileSystemExceptionClass;
                    JFileSystemException();
                    JFileSystemException(JClass* _class);
                    JFileSystemException(JClass* _class,JString file);
                    JFileSystemException(JClass* _class,JString file,JString other,JString reason);

                public:
                    static JClass* getClazz();
                    JFileSystemException(JString file);
                    JFileSystemException(JString file,JString other,JString reason);
                    virtual JString getFile();
                    virtual JString getOtherFile();
                    virtual JString getReason();
                    virtual ~JFileSystemException();
            };
        }
    }
}

#endif // JFILESYSTEMEXCEPTION_H
