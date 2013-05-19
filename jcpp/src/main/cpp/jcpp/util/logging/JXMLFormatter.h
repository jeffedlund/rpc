#ifndef JXMLFORMATTER_H
#define JXMLFORMATTER_H

#include "JFormatter.h"
#include "JString.h"
#include "JHandler.h"
#include "JLogRecord.h"
#include "JStringBuffer.h"
#include "JLogManager.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JXMLFormatter : public JFormatter  {
                protected:
                    JLogManager* manager;
                    void a2(JStringBuffer* sb, jint x);
                    void appendISO8601(JStringBuffer* sb, jlong millis);
                    void escape(JStringBuffer* sb, JString text);
                    friend class JXMLFormatterClass;

                public:
                    static JClass* getClazz();
                    JXMLFormatter();
                    virtual JString format(JLogRecord* record);
                    virtual JString getHead(JHandler* handler);
                    virtual JString getTail(JHandler* handler);
                    virtual ~JXMLFormatter();
            };
        }
    }
}

#endif // JXMLFORMATTER_H
