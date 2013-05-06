#ifndef JPIPEDINPUTSTREAM_H
#define JPIPEDINPUTSTREAM_H

#include "JInputStream.h"

namespace jcpp{
    namespace io{
        class JPipedOutputStream;
        class JPipedInputStream : public JInputStream  {
            protected:
                jbool closedByWriter;
                jbool closedByReader;
                jbool connected;
                jbyte* buffer;
                jint length;
                jint in;
                jint out;
                void initPipe(jint pipeSize);
                void receive(jint b);
                void receive(jbyte b[],jint off,jint len);
                void checkStateForReceive();
                void awaitSpace();
                void receivedLast();
                friend class JPipedOutputStream;

            public:
                static JClass* getClazz();
                JPipedInputStream(JPipedOutputStream* src,jint pipeSize=2014);
                JPipedInputStream(jint pipeSize=2014);
                virtual void connect(JPipedOutputStream* src);
                virtual jint peek();//TODO remove ?
                virtual jint read();
                virtual jint read(jbyte b[],jint off,jint len);
                virtual jint available();
                virtual void close();
                virtual ~JPipedInputStream();
        };
    }
}

#endif // JPIPEDINPUTSTREAM_H
