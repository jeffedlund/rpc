#ifndef JPROVIDERMISMATCHEXCEPTION_H
#define JPROVIDERMISMATCHEXCEPTION_H

#include "JIllegalArgumentException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JProviderMismatchException : public JIllegalArgumentException  {
                public:
                    static JClass* getClazz();
                    JProviderMismatchException();
                    JProviderMismatchException(string msg);
                    virtual ~JProviderMismatchException();
            };
        }
    }
}

#endif // JPROVIDERMISMATCHEXCEPTION_H
