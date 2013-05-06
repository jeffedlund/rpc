#ifndef JPIPEDREADER_H
#define JPIPEDREADER_H

#include "JReader.h"
#include "JPipedWriter.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JPipedReader : public JReader  {
            protected:
                jbool closedByWriter;
                jbool closedByReader;
                jbool connected;
                jchar* buffer;
                jint length;
                jint in;
                jint out;
                void initPipe(jint pipeSize);
                void receive(jint c);
                void receive(jchar c[],jint off,jint len);
                void receivedLast();
                friend class JPipedWriter;

            public:
                static JClass* getClazz();
                JPipedReader(JPipedWriter* src, jint pipeSize=1024);
                JPipedReader(jint pipeSize=1024);
                virtual void connect(JPipedWriter* src);
                virtual jint read();
                virtual jint read(jchar cbuf[], jint off, jint len);
                virtual jbool ready();
                virtual void close();
                virtual ~JPipedReader();
        };
    }
}

#endif // JPIPEDREADER_H
