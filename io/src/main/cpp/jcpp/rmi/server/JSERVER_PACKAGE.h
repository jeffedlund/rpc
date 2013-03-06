#ifndef JSERVER_PACKAGE_H
#define JSERVER_PACKAGE_H

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

                virtual ~JSERVER_PACKAGE();
            };
        }
    }
}

#endif // JSERVER_PACKAGE_H
