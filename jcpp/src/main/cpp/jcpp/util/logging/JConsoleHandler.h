#ifndef JCONSOLEHANDLER_H
#define JCONSOLEHANDLER_H

#include "JStreamHandler.h"
#include "JLogRecord.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JConsoleHandler : public JStreamHandler  {
                protected:
                    void configure();
                public:
                    static JClass* getClazz();
                    JConsoleHandler();
                    virtual void close();
                    virtual void publish(JLogRecord* record);
                    virtual ~JConsoleHandler();

            };
        }
    }
}

#endif // JCONSOLEHANDLER_H
