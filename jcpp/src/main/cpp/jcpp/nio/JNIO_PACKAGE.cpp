#include "JNIO_PACKAGE.h"
#include "JCPP_PACKAGE.h"
#include "JNIO_FILE_PACKAGE.h"

namespace jcpp{
    namespace nio{
        JNIO_PACKAGE::JNIO_PACKAGE():JPackage("jcpp.nio",JPackage::getClazz()){//better class
        }

        JPackage* JNIO_PACKAGE::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        vector<JPackage*>* JNIO_PACKAGE::getPackages(){
            if (packages->size()==0){
                packages->push_back(JNIO_FILE_PACKAGE::getPackage());
            }
            return packages;
        }

        static JNIO_PACKAGE* jNIO_PACKAGE=NULL;

        JNIO_PACKAGE* JNIO_PACKAGE::getPackage(){
            if (jNIO_PACKAGE==NULL){
                jNIO_PACKAGE=new JNIO_PACKAGE();
            }
            return jNIO_PACKAGE;
        }

        JNIO_PACKAGE::~JNIO_PACKAGE(){
        }
    }
}


