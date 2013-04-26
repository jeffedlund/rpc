#ifndef JFILEREADER_H
#define JFILEREADER_H

#include "JInputStreamReader.h"
#include "JFile.h"

namespace jcpp{
    namespace io{
        class JFileReader : public JInputStreamReader  {
            public:
                static JClass* getClazz();
                JFileReader(string name);
                JFileReader(JFile* f);
                virtual ~JFileReader();
        };
    }
}

#endif // JFILEREADER_H
