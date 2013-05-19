#ifndef JSIMPLEFORMATTER_H
#define JSIMPLEFORMATTER_H

#include "JString.h"
#include "JFormatter.h"
#include "JLogRecord.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JSimpleFormatter : public JFormatter  {
                protected:
                    friend class JSimpleFormatterClass;

                public:
                    static JClass* getClazz();
                    JSimpleFormatter();
                    virtual JString format(JLogRecord* record);
                    virtual ~JSimpleFormatter();
            };
        }
    }
}

#endif // JSIMPLEFORMATTER_H

//            
