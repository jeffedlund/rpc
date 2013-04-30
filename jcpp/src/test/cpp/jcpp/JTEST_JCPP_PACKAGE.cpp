#include "JTEST_JCPP_PACKAGE.h"

namespace jcpp{
    JTEST_JCPP_PACKAGE::JTEST_JCPP_PACKAGE():JPackage("jcpp",JPackage::getClazz()){//better class
        classes->push_back(JTestLauncher::getClazz());
        classes->push_back(JSampleObject::getClazz());
        classes->push_back(JExternalizableObject::getClazz());
        classes->push_back(JEnumSample::getClazz());
        classes->push_back(JIRemoteSample::getClazz());
        classes->push_back(JIRemoteSampleProxy::getClazz());
        classes->push_back(JRemoteSample::getClazz());
    }

    JPackage* JTEST_JCPP_PACKAGE::getSuperPackage(){
        return NULL;
    }

    vector<JPackage*>* JTEST_JCPP_PACKAGE::getPackages(){
        if (packages->size()==0){
        }
        return packages;
    }

    static JTEST_JCPP_PACKAGE* jcpp=NULL;

    JTEST_JCPP_PACKAGE* JTEST_JCPP_PACKAGE::getPackage(){
        if (jcpp==NULL){
            jcpp=new JTEST_JCPP_PACKAGE();
        }
        return jcpp;
    }

    JTEST_JCPP_PACKAGE::~JTEST_JCPP_PACKAGE(){
    }
}

