#ifndef JINTERRUPTEDIOEXCEPTION_H
#define JINTERRUPTEDIOEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JInterruptedIOException : public JIOException  {
            protected:
                JPrimitiveInt* bytesTransferred;

            public:
                static JClass* getClazz();
                JInterruptedIOException();
                JPrimitiveInt* getBytesTransferred();
                void setBytesTransferred(JPrimitiveInt* bt);
                virtual ~JInterruptedIOException();
        };
    }
}

#endif // JINTERRUPTEDIOEXCEPTION_H
