#ifndef JWATCHKEY_H
#define JWATCHKEY_H

#include "JWatchable.h"
#include "JList.h"
#include "JInterface.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace nio{
        namespace file{
            class JWatchable;
            class JCPP_LIBRARY_EXPORT JWatchKey : public JInterface  {
                public:
                    static JClass* getClazz();
                    virtual jbool isValid()=0;
                    virtual JList* pollEvents()=0;
                    virtual jbool reset()=0;
                    virtual void cancel()=0;
                    virtual JWatchable* watchable()=0;
                    virtual ~JWatchKey();
            };
        }
    }
}

#endif // JWATCHKEY_H
