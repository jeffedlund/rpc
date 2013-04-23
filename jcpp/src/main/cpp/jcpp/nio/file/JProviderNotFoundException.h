#ifndef JPROVIDERNOTFOUNDEXCEPTION_H
#define JPROVIDERNOTFOUNDEXCEPTION_H

#include "JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JProviderNotFoundException : public JRuntimeException  {
                public:
                    static JClass* getClazz();
                    JProviderNotFoundException();
                    JProviderNotFoundException(string msg);
                    virtual ~JProviderNotFoundException();
            };
        }
    }
}

#endif // JPROVIDERNOTFOUNDEXCEPTION_H
