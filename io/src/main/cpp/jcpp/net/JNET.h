#ifndef JNET_H
#define JNET_H

#include "JInetAddress.h"
#include "JInet4Address.h"
#include "JInet6Address.h"
#include "JSocket.h"
#include "JServerSocket.h"
#include "JPackage.h"
#include "JCPP.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{
        class JCPP_LIBRARY_EXPORT JNET : public JPackage{
        protected:
            JNET();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JNET* getPackage();

            virtual ~JNET();
        };
    }
}

#endif // JNET_H
