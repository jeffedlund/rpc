#ifndef JHANDLER_H
#define JHANDLER_H

#include "JObject.h"
#include "JErrorManager.h"
#include "JFilter.h"
#include "JLevel.h"
#include "JString.h"
#include "JLogRecord.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JLogManager;
            class JFormatter;
            class JHandler : public JObject  {
                protected:
                    JLogManager* logManager;
                    JFilter* filter;
                    JFormatter* formatter;
                    JLevel* logLevel;
                    JErrorManager* errorManager;
                    JString* encoding;
                    jbool sealed;
                    JHandler(JClass* _class);
                    void reportError(JString msg, JException* ex, jint code);

                public:
                    static JClass* getClazz();
                    virtual void publish(JLogRecord* lr)=0;
                    virtual void flush()=0;
                    virtual void close()=0;
                    virtual void setFormatter(JFormatter* f);
                    virtual JFormatter* getFormatter();
                    virtual void setEncoding(JString enc);
                    virtual JString* getEncoding();
                    virtual void setFilter(JFilter* f);
                    virtual JFilter* getFilter();
                    virtual void setErrorManager(JErrorManager* em);
                    virtual JErrorManager* getErrorManager();
                    virtual void setLevel(JLevel* l);
                    virtual JLevel* getLevel();
                    virtual jbool isLoggable(JLogRecord* lr);
                    virtual ~JHandler();

            };
        }
    }
}

#endif // JHANDLER_H
