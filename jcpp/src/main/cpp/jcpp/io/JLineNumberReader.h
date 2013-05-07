#ifndef JLINENUMBERREADER_H
#define JLINENUMBERREADER_H

#include "JString.h"
#include "JBufferedReader.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JLineNumberReader : public JBufferedReader  {
            protected:
                jint lineNumber;
                jint markedLineNumber;
                jbool skipLF;
                jbool markedSkipLF;
                jchar* skipBuffer;
                jint length;

            public:
                static JClass* getClazz();
                JLineNumberReader(JReader* in,jint sz);
                JLineNumberReader(JReader* in);
                virtual void  setLineNumber(jint lineNumber);
                virtual jint getLineNumber();
                virtual jint read();
                virtual jint read(jchar cbuf[], jint off, jint len);
                virtual string readLine();
                virtual jlong skip(jlong n);
                virtual void mark(jint m);
                virtual void reset();
                virtual ~JLineNumberReader();
        };
    }
}

#endif // JLINENUMBERREADER_H
