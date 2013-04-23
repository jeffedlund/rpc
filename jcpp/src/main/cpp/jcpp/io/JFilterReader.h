#ifndef JFILTERREADER_H
#define JFILTERREADER_H

#include "JReader.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFilterReader : public JReader  {
            protected:
                JReader* in;
                JFilterReader(JClass* _class,JReader* in);

            public:
                static JClass* getClazz();
                virtual jint read();
                virtual jint read(jchar cbuf[], jint off, jint len);
                virtual jlong skip(jlong n);
                virtual jbool ready();
                virtual jbool markSupported();
                virtual void  mark(jint m);
                virtual void  reset();
                virtual void  close();
                virtual ~JFilterReader();
        };
    }
}

#endif // JFILTERREADER_H
