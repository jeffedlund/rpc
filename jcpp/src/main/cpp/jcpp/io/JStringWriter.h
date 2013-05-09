#ifndef JSTRINGWRITER_H
#define JSTRINGWRITER_H

#include "JAppendable.h"
#include "JString.h"
#include "JWriter.h"
#include "JCharSequence.h"
#include "JStringBuffer.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JStringWriter : public JWriter  {
            protected:
                JStringBuffer* buf;

            public:
                static JClass* getClazz();
                JStringWriter();
                virtual void write(jint c);
                virtual void write(jchar buf[],jint off,jint len);
                virtual void write(JString* str);
                virtual void write(JString str);
                virtual void write(JString* str,jint off,jint len);
                virtual void write(JString str,jint off,jint len);
                virtual JStringWriter* append(JCharSequence* csq);
                virtual JStringWriter* append(JCharSequence* csq,jint start,jint end);
                virtual JStringWriter* append(jchar c);
                virtual JString toString();
                virtual JStringBuffer* getBuffer();
                virtual void flush();
                virtual void close();
                virtual ~JStringWriter();
        };
    }
}

#endif // JSTRINGWRITER_H
