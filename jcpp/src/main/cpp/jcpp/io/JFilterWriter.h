#ifndef JFILTERWRITER_H
#define JFILTERWRITER_H

#include "JString.h"
#include "JWriter.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFilterWriter : public JWriter  {
            protected:
                JWriter* out;
                JFilterWriter(JClass* _class,JWriter* out);

            public:
                static JClass* getClazz();
                virtual void write(jint c);
                virtual void  write(jchar cbuf[], jint off, jint len);
                virtual void  write(JString* str, jint off, jint len);
                virtual void  flush();
                virtual void  close();
                virtual ~JFilterWriter();
        };
    }
}

#endif // JFILTERWRITER_H
