#ifndef JFILEFILTER_H
#define JFILEFILTER_H

#include "JInterface.h"
#include "Object.h"
#include "JCPP.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JFile;
        class JCPP_LIBRARY_EXPORT JFileFilter : public JInterface  {
            public:
                static JClass* getClazz();
                virtual jbool accept(JFile* file)=0;
                virtual ~JFileFilter();
        };
    }
}

#endif // JFILEFILTER_H
