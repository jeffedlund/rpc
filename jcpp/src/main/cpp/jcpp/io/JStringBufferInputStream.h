#ifndef JSTRINGBUFFERINPUTSTREAM_H
#define JSTRINGBUFFERINPUTSTREAM_H

#include "JInputStream.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JStringBufferInputStream : public JInputStream  {
            protected:
                JString buffer;
                jint pos;
                jint count;

            public:
                static JClass* getClazz();
                JStringBufferInputStream(JString s);
                virtual jint read();
                virtual jint read(jbyte b[], jint offset, jint len);
                virtual jlong skip(jlong n);
                virtual jint available();
                virtual void reset();
                virtual ~JStringBufferInputStream();

        };
    }
}

#endif // JSTRINGBUFFERINPUTSTREAM_H
