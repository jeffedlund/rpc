#ifndef JNIO_PACKAGE_H
#define JNIO_PACKAGE_H

#include "JCPP_PACKAGE.h"
#include "JREFLECT.h"
#include "JCPP.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace nio{
        class JCPP_LIBRARY_EXPORT JNIO_PACKAGE : public JPackage{
        protected:
            JNIO_PACKAGE();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JNIO_PACKAGE* getPackage();

            virtual ~JNIO_PACKAGE();
        };
    }
}

#endif // JNIO_PACKAGE_H
