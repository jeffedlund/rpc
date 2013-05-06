#ifndef JPIPEDWRITER_H
#define JPIPEDWRITER_H

#include "JWriter.h"

namespace jcpp{
    namespace io{
        class JPipedReader;
        class JCPP_LIBRARY_EXPORT JPipedWriter : public JWriter  {
            protected:
                JPipedReader* sink;
                jbool closed;

            public:
                static JClass* getClazz();
                JPipedWriter(JPipedReader* snk);
                JPipedWriter();
                virtual void connect(JPipedReader* snk);
                virtual void write(jint c);
                virtual void write(jchar cbuf[], jint off, jint len);
                virtual void flush();
                virtual void close();
                virtual ~JPipedWriter();
        };
    }
}

#endif // JPIPEDWRITER_H
