#ifndef JINVALIDPATHEXCEPTION_H
#define JINVALIDPATHEXCEPTION_H

#include "JIllegalArgumentException.h"
#include "JString.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JInvalidPathException : public JIllegalArgumentException  {
                protected:
                    JString* input;
                    JPrimitiveInt* index;
                    friend class JInvalidPathExceptionClass;

                public:
                    static JClass* getClazz();
                    JInvalidPathException();
                    JInvalidPathException(string input,string reason,jint index=-1);
                    virtual string getInput();
                    virtual string getReason();
                    virtual jint getIndex();
                    virtual ~JInvalidPathException();
            };
        }
    }
}

#endif // JINVALIDPATHEXCEPTION_H
