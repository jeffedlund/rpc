#ifndef JFILENAMEFILTER_H
#define JFILENAMEFILTER_H

#include "JInterface.h"
#include "JString.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JFile;
        class JCPP_LIBRARY_EXPORT JFilenameFilter : public JInterface  {
            public:
                static JClass* getClazz();
                virtual jbool accept(JFile* dir, JString name)=0;
                virtual ~JFilenameFilter();
        };
    }
}

#endif // JFILENAMEFILTER_H
