#ifndef JINET4ADDRESS_H
#define JINET4ADDRESS_H

#include "JLANG.h"
#include "JIO.h"
#include "JInetAddress.h"

namespace jcpp{
    namespace net{
        class JInet4Address : public JInetAddress{
        protected:

        public:
            JInet4Address();
            static JClass* getClazz();
        };
    }
}

#endif // JINET4ADDRESS_H