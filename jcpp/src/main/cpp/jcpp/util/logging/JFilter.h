#ifndef JFILTER_H
#define JFILTER_H

#include "JInterface.h"
#include "JLogRecord.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JFilter : public JInterface  {
                public:
                    static JClass* getClazz();
                    virtual jbool isLoggable(JLogRecord* lr)=0;
                    virtual ~JFilter();
            };
        }
    }
}

#endif // JFILTER_H
