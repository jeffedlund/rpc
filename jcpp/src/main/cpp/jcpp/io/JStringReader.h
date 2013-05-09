#ifndef JSTRINGREADER_H
#define JSTRINGREADER_H

#include "JReader.h"
#include "JString.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JStringReader : public JReader  {
            protected:
                JString str;
                jint length;
                jint next;
                jint imark;

            public:
                static JClass* getClazz();
                JStringReader(JString s);
                virtual jint read();
                virtual jint read(jchar cbuf[], jint off, jint len);
                virtual jlong skip(jlong n);
                virtual jbool ready();
                virtual jbool markSupported();
                virtual void mark(jint m);
                virtual void reset();
                virtual void close();
                virtual ~JStringReader();
        };
    }
}

#endif // JSTRINGREADER_H
