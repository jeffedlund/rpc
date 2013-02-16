#ifndef JNET_H
#define JNET_H

#include "JInetAddress.h"
#include "JSocket.h"
#include "JServerSocket.h"
#include "JPackage.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{
        class JNET : public JPackage{
        protected:
            JNET();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JNET* getPackage();
        };
    }
}

#endif // JNET_H
