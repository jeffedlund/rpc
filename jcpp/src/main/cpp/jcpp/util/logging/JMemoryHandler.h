#ifndef JMEMORYHANDLER_H
#define JMEMORYHANDLER_H

#include "JLevel.h"
#include "JLogRecord.h"
#include "JHandler.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JMemoryHandler : public JHandler  {
                protected:
                    JLevel* pushLevel;
                    jint size;
                    JHandler* target;
                    vector<JLogRecord*>* buffer;
                    jint start;
                    jint count;
                    void init();
                    void configure();
                    friend class JMemoryHandlerClass;

                public:
                    static JClass* getClazz();
                    JMemoryHandler();
                    JMemoryHandler(JHandler* target, jint size, JLevel* pushLevel);
                    virtual void publish(JLogRecord* record);
                    virtual void push();
                    virtual void flush();
                    virtual void close();
                    virtual void setPushLevel(JLevel* l);
                    virtual JLevel* getPushLevel();
                    virtual jbool isLoggable(JLogRecord* record);
                    virtual ~JMemoryHandler();
            };
        }
    }
}

#endif // JMEMORYHANDLER_H
