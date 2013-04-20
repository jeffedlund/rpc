#ifndef JSYNCFAILEDEXCEPTION_H
#define JSYNCFAILEDEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JSyncFailedException : public JIOException  {
            public:
                static JClass* getClazz();
                JSyncFailedException();
                virtual ~JSyncFailedException();
        };
    }
}

#endif // JSYNCFAILEDEXCEPTION_H
