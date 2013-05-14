#ifndef JBUFFEREDWRITER_H
#define JBUFFEREDWRITER_H

#include "JWriter.h"
#include "JString.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JBufferedWriter : public JWriter  {
            protected:
                JWriter* out;
                jchar* cb;
                jint size;
                jint nChars;
                jint nextChar;
                JString lineSeparator;
                void ensureOpen();
                void flushBuffer();

            public:
                static JClass* getClazz();
                JBufferedWriter(JWriter* out,jint size=8192);
                virtual void write(jint c);
                virtual void write(jchar cbuf[], jint off, jint len);
                virtual void write(JString* str, jint off, jint len);
                virtual void newLine();
                virtual void flush();
                virtual void close();
                virtual ~JBufferedWriter();
        };
    }
}

#endif // JBUFFEREDWRITER_H
