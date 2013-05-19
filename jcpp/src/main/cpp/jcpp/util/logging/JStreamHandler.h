#ifndef JSTREAMHANDLER_H
#define JSTREAMHANDLER_H

#include "JString.h"
#include "JLogRecord.h"
#include "JHandler.h"
#include "JLogManager.h"
#include "JOutputStream.h"
#include "JWriter.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        namespace logging{
            class JStreamHandler : public JHandler  {
                protected:
                    JLogManager* manager;
                    JOutputStream* output;
                    jbool doneHeader;
                    JWriter* writer;
                    JStreamHandler(JClass* _class);
                    virtual void configure();
                    virtual void setOutputStream(JOutputStream* out);
                    virtual void flushAndClose();
                    friend class JStreamHandlerClass;

                public:
                    static JClass* getClazz();
                    JStreamHandler();
                    JStreamHandler(JOutputStream* out, JFormatter* formatter);
                    virtual void setEncoding(JString encoding);
                    virtual void publish(JLogRecord* record);
                    virtual jbool isLoggable(JLogRecord* record);
                    virtual void flush();
                    virtual void close();
                    virtual ~JStreamHandler();
            };
        }
    }
}

#endif // JSTREAMHANDLER_H
