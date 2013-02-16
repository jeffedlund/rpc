#ifndef JSERVER_H
#define JSERVER_H

#include "JRMI.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            class JSERVER : public JPackage{
            protected:
                JSERVER();

            public:
                JPackage* getSuperPackage();

                vector<JPackage*>* getPackages();

                static JSERVER* getPackage();
            };
        }
    }
}

#endif // JSERVER_H
