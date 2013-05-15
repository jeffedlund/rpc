#ifndef JPUSHBACKREADER_H
#define JPUSHBACKREADER_H

#include "JFilterReader.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JPushbackReader : public JFilterReader  {
            protected:
                jchar* buf;
                jint pos;
                jint length;
                void ensureOpen();

            public:
                static JClass* getClazz();
                JPushbackReader(JReader* in,jint size=1);
                virtual jint read();
                virtual jint read(jchar cbuf[], jint off, jint len);
                virtual void unread(jint c);
                virtual void unread(jchar cbuf[], jint off, jint len);
                virtual jbool ready();
                virtual void mark(jint m);
                virtual void reset();
                virtual jbool markSupported();
                virtual void close();
                virtual jlong skip(jlong n);
                virtual ~JPushbackReader();
        };
    }
}

#endif // JPUSHBACKREADER_H
