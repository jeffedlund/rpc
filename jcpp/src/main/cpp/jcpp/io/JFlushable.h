#ifndef JFLUSHABLE_H
#define JFLUSHABLE_H

#include "JInterface.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
       class JFlushable : public JInterface {
            public:
                static JClass* getClazz();
                virtual void  flush()=0;
                virtual ~JFlushable();
        };
    }
}

#endif // JFLUSHABLE_H
