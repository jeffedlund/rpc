#ifndef JIOERROR_H
#define JIOERROR_H

#include "JError.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JIOError : public JError {
            public:
                static JClass* getClazz();
                JIOError(string message);
                JIOError();
                JIOError(JThrowable* cause);
                virtual ~JIOError();
        };
    }
}

#endif // JIOERROR_H
