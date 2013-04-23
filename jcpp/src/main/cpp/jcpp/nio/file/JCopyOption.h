#ifndef JCOPYOPTION_H
#define JCOPYOPTION_H

#include "JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JCPP_LIBRARY_EXPORT JCopyOption : public JInterface  {
                public:
                    static JClass* getClazz();
                    virtual ~JCopyOption();
            };
        }
    }
}

#endif // JCOPYOPTION_H
