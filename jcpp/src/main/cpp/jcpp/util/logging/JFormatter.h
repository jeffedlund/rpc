#ifndef JFORMATTER_H
#define JFORMATTER_H

#include "JObject.h"
#include "JHandler.h"
#include "JString.h"
#include "JLogRecord.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JFormatter : public JObject  {
                protected:
                    JFormatter(JClass* _class);

                public:
                    static JClass* getClazz();
                    virtual JString format(JLogRecord* lr)=0;
                    virtual JString getHead(JHandler* h);
                    virtual JString getTail(JHandler* h);
                    virtual JString formatMessage(JLogRecord* lr);
                    virtual ~JFormatter();
            };
        }
    }
}

#endif // JFORMATTER_H
