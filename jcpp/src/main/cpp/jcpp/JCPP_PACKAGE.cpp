#include "JCPP_PACKAGE.h"
#include "JIO.h"
#include "JUTIL.h"
#include "JLANG.h"
#include "JNET.h"
#include "JRMI.h"
#include "JSECURITY_PACKAGE.h"
#include "JNIO_PACKAGE.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::lang;
using namespace jcpp::net;
using namespace jcpp::rmi;
using namespace jcpp::security;
using namespace jcpp::nio;

namespace jcpp{
    JCPP_PACKAGE::JCPP_PACKAGE():JPackage("jcpp",JPackage::getClazz()){//better class
    }

    JPackage* JCPP_PACKAGE::getSuperPackage(){
        return NULL;
    }

    vector<JPackage*>* JCPP_PACKAGE::getPackages(){
        if (packages->size()==0){
            packages->push_back(JIO::getPackage());
            packages->push_back(JUTIL::getPackage());
            packages->push_back(JLANG::getPackage());
            packages->push_back(JNET::getPackage());
            packages->push_back(JRMI::getPackage());
            packages->push_back(JSECURITY_PACKAGE::getPackage());
            packages->push_back(JNIO_PACKAGE::getPackage());
        }
        return packages;
    }

    static JCPP_PACKAGE* jcpp=NULL;

    JCPP_PACKAGE* JCPP_PACKAGE::getPackage(){
        if (jcpp==NULL){
            jcpp=new JCPP_PACKAGE();
        }
        return jcpp;
    }

    JCPP_PACKAGE::~JCPP_PACKAGE(){
    }
}
