#ifndef JINPUTSTREAMREADER_H
#define JINPUTSTREAMREADER_H

#include "JReader.h"
#include "JString.h"
#include "JInputStream.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JInputStreamReader : public JReader  {
            protected:
                JInputStream* in;

            public:
                static JClass* getClazz();
                JInputStreamReader(JInputStream* in);
                virtual jint read();
                virtual jint read(jchar cbuf[],jint offset, jint length);
                virtual jbool ready();
                virtual void  close();
                virtual ~JInputStreamReader();
        };
    }
}

#endif // JINPUTSTREAMREADER_H
