#ifndef JOBJECTINPUTVALIDATION_H
#define JOBJECTINPUTVALIDATION_H

#include "JInterface.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JObjectInputValidation : public JInterface  {
            public:
                static JClass* getClazz();
                virtual void validateObject()=0;
                virtual ~JObjectInputValidation();
        };
    }
}

#endif
