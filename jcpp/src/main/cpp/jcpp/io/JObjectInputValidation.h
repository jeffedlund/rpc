#ifndef JOBJECTINPUTVALIDATION_H
#define JOBJECTINPUTVALIDATION_H

#include "JInterface.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JObjectInputValidation : public JInterface  {
            public:
                static JClass* getClazz();
                virtual void  validateObject()=0;
                virtual ~JObjectInputValidation();
        };
    }
}

#endif
