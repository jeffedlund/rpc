#ifndef JSERVER_H
#define JSERVER_H

#include "JRMI.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            class JSERVER_PACKAGE : public JPackage{
            protected:
                JSERVER_PACKAGE();

            public:
                JPackage* getSuperPackage();

                vector<JPackage*>* getPackages();

                static JSERVER_PACKAGE* getPackage();
            };
        }
    }
}

#endif // JSERVER_H