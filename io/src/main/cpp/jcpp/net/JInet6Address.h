#ifndef JINET6ADDRESS_H
#define JINET6ADDRESS_H

#include "JLANG.h"
#include "JIO.h"
#include "JInetAddress.h"

namespace jcpp{
    namespace net{
        class JInet6Address : public JInetAddress{
        protected:

        public:
            JInet6Address();
            static JClass* getClazz();
        };
    }
}

#endif // JINET6ADDRESS_H
