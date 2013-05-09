#ifndef JFILEREADER_H
#define JFILEREADER_H

#include "JInputStreamReader.h"
#include "JFile.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFileReader : public JInputStreamReader  {
            public:
                static JClass* getClazz();
                JFileReader(JString name);
                JFileReader(JFile* f);
                virtual ~JFileReader();
        };
    }
}

#endif // JFILEREADER_H
