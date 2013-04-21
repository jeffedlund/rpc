#ifndef JPIPEDOUTPUTSTREAM_H
#define JPIPEDOUTPUTSTREAM_H

#include "JOutputStream.h"
#include "JPipedInputStream.h"

namespace jcpp{
    namespace io{
        class JPipedOutputStream : public JOutputStream  {
            protected:
                JPipedInputStream* sink;

            public:
                static JClass* getClazz();
                JPipedOutputStream(JPipedInputStream* sink);
                JPipedOutputStream();
                virtual void  connect(JPipedInputStream* sink);
                virtual void  write(jint b);
                virtual void  write(jbyte b[], jint off, jint len);
                virtual void  flush();
                virtual void  close();
                virtual ~JPipedOutputStream();
        };
    }
}

#endif // JPIPEDOUTPUTSTREAM_H
