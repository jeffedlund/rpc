#ifndef JTEST_JCPP_PACKAGE_H
#define JTEST_JCPP_PACKAGE_H

#include "vector"
#include <iostream>
#include "JPackage.h"
#include "JTestLauncher.h"
#include "JSampleObject.h"
#include "JExternalizableObject.h"
#include "JEnumSample.h"
#include "JIRemoteSample.h"
#include "JIRemoteSampleProxy.h"
#include "JRemoteSample.h"

using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    class JTEST_JCPP_PACKAGE : public JPackage{
    protected:
        JTEST_JCPP_PACKAGE();

    public:
        JPackage* getSuperPackage();

        vector<JPackage*>* getPackages();

        static JTEST_JCPP_PACKAGE* getPackage();

        virtual ~JTEST_JCPP_PACKAGE();
    };
}

#endif // JTEST_JCPP_PACKAGE_H
