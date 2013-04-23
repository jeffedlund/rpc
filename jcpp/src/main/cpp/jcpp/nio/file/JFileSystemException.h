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
                    JFileSystemException(JClass* _class,string file);
                    JFileSystemException(JClass* _class,string file,string other,string reason);

                public:
                    static JClass* getClazz();
                    JFileSystemException(string file);
                    JFileSystemException(string file,string other,string reason);
                    virtual string getFile();
                    virtual string getOtherFile();
                    virtual string getReason();
                    virtual ~JFileSystemException();
            };
        }
    }
}

#endif // JFILESYSTEMEXCEPTION_H
