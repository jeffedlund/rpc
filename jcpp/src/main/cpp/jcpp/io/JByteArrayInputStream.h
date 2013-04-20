#ifndef JBYTEARRAYINPUTSTREAM_H
#define JBYTEARRAYINPUTSTREAM_H

#include "JInputStream.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JByteArrayInputStream : public JInputStream  {
            protected:
                jbyte* buf;
                jint pos;
                jint imark;
                jint count;
            public:
                static JClass* getClazz();
                JByteArrayInputStream(jbyte buf[],jint l);
                JByteArrayInputStream(jbyte buf[],jint offset,jint l);
                virtual jint read();
                virtual jint read(jbyte b[], jint off, jint l);
                virtual jlong skip(jlong l);
                virtual jint available();
                virtual jbool markSupported();
                virtual void  mark(jint m);
                virtual void  reset();
                virtual void  close();
                virtual ~JByteArrayInputStream();
        };
    }
}

#endif // JBYTEARRAYINPUTSTREAM_H
