#ifndef JFILEWRITER_H
#define JFILEWRITER_H

#include "JOutputStreamWriter.h"
#include "JFile.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFileWriter : public JOutputStreamWriter  {
            public:
                static JClass* getClazz();
                JFileWriter(string filename,jbool append=false);
                JFileWriter(JFile* f,jbool append=false);
                virtual ~JFileWriter();
        };
    }
}

#endif // JFILEWRITER_H
