#ifndef JCHARARRAYWRITER_H
#define JCHARARRAYWRITER_H

#include "JString.h"
#include "JCharSequence.h"
#include "JWriter.h"
#include "JAppendable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JCharArrayWriter : public JWriter  {
            protected:
                vector<jchar>* buf;

            public:
                static JClass* getClazz();
                JCharArrayWriter();
                virtual void write(jint c);
                virtual void write(jchar c[], jint offset, jint len);
                virtual void write(JString* str, jint offset, jint len);
                virtual void write(JString str, jint offset, jint len);
                virtual void writeTo(JWriter* out);
                virtual JCharArrayWriter* append(JCharSequence* csq);
                virtual JCharArrayWriter* append(JCharSequence* csq,jint offset,jint len);
                virtual JCharArrayWriter * append(jchar c);
                virtual void reset();
                virtual vector<jchar>* toCharArray();
                virtual jint size();
                virtual JString toString();
                virtual void flush();
                virtual void close();
                virtual ~JCharArrayWriter();
        };
    }
}

#endif // JCHARARRAYWRITER_H
