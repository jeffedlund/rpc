#include "JTestPackageLoader.h"
#include "JTEST_JCPP_PACKAGE.h"

using namespace jcpp;

JPackage* JTestPackageLoader::getPackage(){
    return JTEST_JCPP_PACKAGE::getPackage();
}

