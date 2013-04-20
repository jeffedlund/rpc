#include "JSECURITY_PACKAGE.h"
#include "JCPP_PACKAGE.h"

using namespace jcpp;

namespace jcpp{
    namespace security{
        JSECURITY_PACKAGE::JSECURITY_PACKAGE():JPackage("jcpp.security",JPackage::getClazz()){//better class
            classes->push_back(JBasicPermission::getClazz());
            classes->push_back(JGuard::getClazz());
            classes->push_back(JPermission::getClazz());
            classes->push_back(JPermissionCollection::getClazz());
        }

        JPackage* JSECURITY_PACKAGE::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        vector<JPackage*>* JSECURITY_PACKAGE::getPackages(){
            if (packages->size()==0){
            }
            return packages;
        }

        static JSECURITY_PACKAGE* jcpp=NULL;

        JSECURITY_PACKAGE* JSECURITY_PACKAGE::getPackage(){
            if (jcpp==NULL){
                jcpp=new JSECURITY_PACKAGE();
            }
            return jcpp;
        }

        JSECURITY_PACKAGE::~JSECURITY_PACKAGE(){
        }
    }
}

