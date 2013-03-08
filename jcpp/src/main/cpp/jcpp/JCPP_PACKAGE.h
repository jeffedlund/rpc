#ifndef JCPPPACKAGE_H
#define JCPPPACKAGE_H

#include "vector"
#include <iostream>
#include "JPackage.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    class JCPP_LIBRARY_EXPORT JCPP_PACKAGE : public JPackage{
    protected:
        JCPP_PACKAGE();

    public:
        JPackage* getSuperPackage();

        vector<JPackage*>* getPackages();

        static JCPP_PACKAGE* getPackage();

        virtual ~JCPP_PACKAGE();
    };
}

#endif // JCPPPACKAGE_H
