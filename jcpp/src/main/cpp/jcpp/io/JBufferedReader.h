#ifndef JBUFFEREDREADER_H
#define JBUFFEREDREADER_H

#include "JString.h"
#include "JReader.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JBufferedReader : public JReader  {
            protected:
                JReader* in;
                jchar* cb;
                jint length;
                jint nChars;
                jint nextChar;
                jint markedChar;
                jint readAheadLimit;
                jbool skipLF;
                jbool markedSkipLF;
                void ensureOpen();
                void fill();
                jint read1(jchar cbuf[], jint off,jint len);
                string readLine(jbool ignoreLF);
                JBufferedReader(JClass* _class,JReader* in,jint sz=8192);

            public:
                static JClass* getClazz();
                JBufferedReader(JReader* in,jint sz=8192);
                virtual jint read();
                virtual jint read(jchar cbuf[], jint off,jint len);
                virtual string readLine();
                virtual jlong skip(jlong n);
                virtual jbool ready();
                virtual jbool markSupported();
                virtual void  mark(jint m);
                virtual void  reset();
                virtual void  close();
                virtual ~JBufferedReader();
        };
    }
}

#endif // JBUFFEREDREADER_H
