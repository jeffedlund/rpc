#ifndef JCPP_H
#define JCPP_H

#include "vector"
#include <iostream>
#include "JPackage.h"
using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    class JCPP : public JPackage{
    protected:
        JCPP();

    public:
        JPackage* getSuperPackage();

        vector<JPackage*>* getPackages();

        static JCPP* getPackage();
    };
}

#endif // JCPP_H
