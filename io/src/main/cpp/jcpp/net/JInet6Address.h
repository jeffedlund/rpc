#ifndef JINET6ADDRESS_H
#define JINET6ADDRESS_H

#include "JLANG.h"
#include "JIO.h"
#include "JInetAddress.h"

namespace jcpp{
    namespace net{
        class JInet6Address : public JInetAddress{//TODO implement
        protected:

        public:
            JInet6Address();
            static JClass* getClazz();
            virtual ~JInet6Address();
        };
    }
}

#endif // JINET6ADDRESS_H
