#include "JCPP.h"
#include "JIO.h"
#include "JUTIL.h"
#include "JLANG.h"
using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::lang;

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
