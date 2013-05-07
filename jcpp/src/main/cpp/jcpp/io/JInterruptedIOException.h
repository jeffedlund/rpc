#ifndef JINTERRUPTEDIOEXCEPTION_H
#define JINTERRUPTEDIOEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JInterruptedIOException : public JIOException  {
            protected:
                JPrimitiveInt* bytesTransferred;
                friend class JInterruptedIOExceptionClass;

            public:
                static JClass* getClazz();
                JInterruptedIOException();
                jint getBytesTransferred();
                void setBytesTransferred(jint bt);
                virtual ~JInterruptedIOException();
        };
    }
}

#endif // JINTERRUPTEDIOEXCEPTION_H
