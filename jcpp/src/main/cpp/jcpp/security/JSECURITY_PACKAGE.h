#ifndef JSECURITY_PACKAGE_H
#define JSECURITY_PACKAGE_H

#include "vector"
#include <iostream>
#include "JPackage.h"
#include "JCPP.h"
#include "JBasicPermission.h"
#include "JGuard.h"
#include "JPermission.h"
#include "JPermissionCollection.h"
#include "JSecureClassLoader.h"

using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace security{
        class JCPP_LIBRARY_EXPORT JSECURITY_PACKAGE : public JPackage{
        protected:
            JSECURITY_PACKAGE();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JSECURITY_PACKAGE* getPackage();

            virtual ~JSECURITY_PACKAGE();
        };
    }
}

#endif // JSECURITY_PACKAGE_H
