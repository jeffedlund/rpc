#include "JCPP.h"
#include "JIO.h"
#include "JUTIL.h"
#include "JLANG.h"
#include "JNET.h"
#include "JRMI.h"
using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::lang;
using namespace jcpp::net;
using namespace jcpp::rmi;

namespace jcpp{
    JCPP::JCPP():JPackage("jcpp",JPackage::getClazz()){//better class
    }

    JPackage* JCPP::getSuperPackage(){
        return NULL;
    }

    vector<JPackage*>* JCPP::getPackages(){
        if (packages->size()==0){
            packages->push_back(JIO::getPackage());
            packages->push_back(JUTIL::getPackage());
            packages->push_back(JLANG::getPackage());
            packages->push_back(JNET::getPackage());
            packages->push_back(JRMI::getPackage());
        }
        return packages;
    }

    static JCPP* jcpp=NULL;

    JCPP* JCPP::getPackage(){
        if (jcpp==NULL){
            jcpp=new JCPP();
        }
        return jcpp;
    }
}
