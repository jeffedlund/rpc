#ifndef JINTERRUPTEDIOEXCEPTION_H
#define JINTERRUPTEDIOEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JInterruptedIOException : public JIOException  {
            protected:
                JPrimitiveInt* bytesTransferred;

            public:
                static JClass* getClazz();
                JInterruptedIOException();
                JPrimitiveInt* getBytesTransferred();
                void setBytesTransferred(JPrimitiveInt* bt);//TODO use only jint
                virtual ~JInterruptedIOException();
        };
    }
}

#endif // JINTERRUPTEDIOEXCEPTION_H
