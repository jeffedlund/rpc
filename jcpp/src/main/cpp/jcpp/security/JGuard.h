#ifndef JGUARD_H
#define JGUARD_H

#include "JObject.h"
#include "JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace security{
        class JCPP_LIBRARY_EXPORT JGuard : public JInterface  {
            public:
                static JClass* getClazz();
                virtual void  checkGuard(JObject*)=0;
                virtual ~JGuard();
        };
    }
}

#endif // JGUARD_H
