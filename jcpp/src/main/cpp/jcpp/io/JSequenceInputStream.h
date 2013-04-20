#ifndef JSEQUENCEINPUTSTREAM_H
#define JSEQUENCEINPUTSTREAM_H

#include "JInputStream.h"
#include "JEnumeration.h"
#include "JVector.h"

using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JSequenceInputStream : public JInputStream  {
            protected:
                JVector* vec;
                JEnumeration* e;
                JInputStream* in;
                void nextStream();

            public:
                static JClass* getClazz();
                JSequenceInputStream(JEnumeration* e);
                JSequenceInputStream(JInputStream* s1,JInputStream* s2);
                virtual void  close();
                virtual jint read(jbyte b[], jint offset, jint len);
                virtual jint read();
                virtual jint available();
                virtual ~JSequenceInputStream();
        };
    }
}

#endif // JSEQUENCEINPUTSTREAM_H
