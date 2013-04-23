#ifndef JNIO_FILE_PACKAGE_H
#define JNIO_FILE_PACKAGE_H

#include "JCPP_PACKAGE.h"
#include "JREFLECT.h"
#include "JCPP.h"
#include "JWatchEvent.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace nio{
        class JCPP_LIBRARY_EXPORT JNIO_FILE_PACKAGE : public JPackage{
        protected:
            JNIO_FILE_PACKAGE();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JNIO_FILE_PACKAGE* getPackage();

            virtual ~JNIO_FILE_PACKAGE();
        };
    }
}

#endif // JNIO_FILE_PACKAGE_H
