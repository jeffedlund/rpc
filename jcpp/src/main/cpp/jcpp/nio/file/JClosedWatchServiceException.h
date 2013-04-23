#ifndef JCLOSEDWATCHSERVICEEXCEPTION_H
#define JCLOSEDWATCHSERVICEEXCEPTION_H

#include "JIllegalStateException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JClosedWatchServiceException : public JIllegalStateException  {
                public:
                    static JClass* getClazz();
                    JClosedWatchServiceException();
                    virtual ~JClosedWatchServiceException();
            };
        }
    }
}

#endif // JCLOSEDWATCHSERVICEEXCEPTION_H
