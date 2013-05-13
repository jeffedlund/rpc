#ifndef JINET6ADDRESS_H
#define JINET6ADDRESS_H

#include "JInetAddress.h"
#include "JCPP.h"

namespace jcpp{
    namespace net{
        class JCPP_LIBRARY_EXPORT JInet6Address : public JInetAddress{//TODO implement
        public:
            JInet6Address();
            static JClass* getClazz();
            virtual ~JInet6Address();
        };
    }
}

#endif // JINET6ADDRESS_H
