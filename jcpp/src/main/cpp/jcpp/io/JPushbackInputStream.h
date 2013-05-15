#ifndef JPUSHBACKINPUTSTREAM_H
#define JPUSHBACKINPUTSTREAM_H

#include "JFilterInputStream.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JPushbackInputStream : public JFilterInputStream  {
            protected:
                jbyte* buf;
                jint length;
                jint pos;
                void ensureOpen();

            public:
                static JClass* getClazz();
                JPushbackInputStream(JInputStream* in,jint size=1);
                virtual jint read();
                virtual jint read(jbyte b[], jint off, jint len);
                virtual void unread(jint b);
                virtual void unread(jbyte b[],jint off,jint len);
                virtual jint available();
                virtual jlong skip(jlong n);
                virtual jbool markSupported();
                virtual void mark(jint r);
                virtual void reset();
                virtual void close();
                virtual ~JPushbackInputStream();
        };
    }
}

#endif // JPUSHBACKINPUTSTREAM_H
