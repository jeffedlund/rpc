#ifndef JOUTPUTSTREAMWRITER_H
#define JOUTPUTSTREAMWRITER_H

#include "JString.h"
#include "JWriter.h"
#include "JOutputStream.h"

using namespace jcpp::lang;

//TODO test and use encoding
namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JOutputStreamWriter : public JWriter  {
            protected:
                JOutputStream* out;
                JOutputStreamWriter(JClass* _class,JOutputStream* out);

            public:
                static JClass* getClazz();
                JOutputStreamWriter(JOutputStream* out,JString encoding="");
                virtual void write(jchar c[],jint offset,jint length);
                virtual void flush();
                virtual void close();
                virtual ~JOutputStreamWriter();
        };
    }
}

#endif // JOUTPUTSTREAMWRITER_H
