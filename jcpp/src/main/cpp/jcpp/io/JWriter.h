#ifndef JWRITER_H
#define JWRITER_H

#include "JWriter.h"
#include "JFlushable.h"
#include "JAppendable.h"
#include "JString.h"
#include "JCharSequence.h"
#include "JObject.h"
#include "JCloseable.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JWriter : public JObject  , public JAppendable  , public JCloseable  , public JFlushable  {
            protected:
                jchar* writeBuffer;
                JObject* lock;
                JWriter(JClass* _class);
                JWriter(JClass* _class,JObject* lock);

            public:
                static JClass* getClazz();
                virtual void write(jint c);
                virtual void write(jchar c[],jint offset,jint length)=0;
                virtual void write(JString* str);
                virtual void write(string str);
                virtual void write(JString* str,jint off,jint len);
                virtual void write(string str,jint off,jint len);
                virtual JWriter* append(JCharSequence* p0 );
                virtual JWriter* append(JCharSequence* p0, jint start, jint end);
                virtual JWriter* append(jchar c);
                virtual void flush()=0;
                virtual void close()=0;
                virtual ~JWriter();
        };
    }
}

#endif // JWRITER_H
