#ifndef JWATCHSERVICE_H
#define JWATCHSERVICE_H

#include "JCloseable.h"
#include "JWatchKey.h"
#include "JInterface.h"

using namespace jcpp::io;
using namespace jcpp::nio::file;
using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JWatchKey;
            class JCPP_LIBRARY_EXPORT JWatchService : public JCloseable  {
                public:
                    static JClass* getClazz();
                    virtual void  close()=0;
                    virtual JWatchKey* poll()=0;
                    virtual JWatchKey* poll(jlong timeout)=0;
                    virtual JWatchKey* take()=0;
                    virtual ~JWatchService();
            };
        }
    }
}

#endif // JWATCHSERVICE_H
