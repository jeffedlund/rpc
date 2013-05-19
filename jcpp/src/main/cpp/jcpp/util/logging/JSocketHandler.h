#ifndef JSOCKETHANDLER_H
#define JSOCKETHANDLER_H

#include "JStreamHandler.h"
#include "JLogRecord.h"
#include "JSocket.h"

using namespace jcpp::net;

namespace jcpp{
    namespace util{
        namespace logging{
            class JSocketHandler : public JStreamHandler  {
                protected:
                    JSocket* sock;
                    JString* host;
                    jint port;
                    JString* portProperty;
                    void configure();
                    void connect();
                    friend class JSocketHandlerClass;

                public:
                    static JClass* getClazz();
                    JSocketHandler();
                    JSocketHandler(JString host,jint port);
                    virtual void close();
                    virtual void publish(JLogRecord* record);
                    virtual ~JSocketHandler();
            };
        }
    }
}

#endif // JSOCKETHANDLER_H
