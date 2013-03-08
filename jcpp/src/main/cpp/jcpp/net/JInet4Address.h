#ifndef JINET4ADDRESS_H
#define JINET4ADDRESS_H

#include "JLANG.h"
#include "JIO.h"
#include "JInetAddress.h"
#include "JCPP.h"

namespace jcpp{
    namespace net{
        class JCPP_LIBRARY_EXPORT JInet4Address : public JInetAddress{//TODO implement
        protected:

        public:
            JInet4Address();
            static JClass* getClazz();
            virtual ~JInet4Address();
        };
    }
}

#endif // JINET4ADDRESS_H