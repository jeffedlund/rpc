#ifndef JWATCHABLE_H
#define JWATCHABLE_H

#include "JWatchEvent.h"
#include "JInterface.h"
#include "JWatchKey.h"
#include "JWatchService.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JWatchService;
            class JWatchKey;
            class JCPP_LIBRARY_EXPORT JWatchable : public JInterface  {
                public:
                    static JClass* getClazz();
                    virtual JWatchKey* registerWS(JWatchService* watcher, vector<JWatchEvent::JKind*>* events, vector<JWatchEvent::JModifier*>* modifiers)=0;
                    virtual JWatchKey * registerWS(JWatchService* watcher, vector<JWatchEvent::JKind*>* events)=0;
                    virtual ~JWatchable();
            };
        }
    }
}

#endif // JWATCHABLE_H
