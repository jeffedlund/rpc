#ifndef JCHARARRAYREADER_H
#define JCHARARRAYREADER_H

#include "JReader.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JCharArrayReader : public JReader  {
            protected:
                jchar* buf;
                jint pos;
                jint markedPos;
                jint count;
                void ensureOpen();

            public:
                static JClass* getClazz();
                JCharArrayReader(jchar buf[]);
                JCharArrayReader(jchar buf[],jint pos,jint length);
                virtual jint read();
                virtual jint read(jchar b[], jint off, jint len);
                virtual jlong skip(jlong n);
                virtual jbool ready();
                virtual jbool markSupported();
                virtual void  mark(jint m);
                virtual void  reset();
                virtual void  close();
                virtual ~JCharArrayReader();
        };
    }
}

#endif // JCHARARRAYREADER_H
