#include "JNIO_FILE_PACKAGE.h"
#include "JNIO_PACKAGE.h"

using namespace jcpp::nio::file;
namespace jcpp{
    namespace nio{
        JNIO_FILE_PACKAGE::JNIO_FILE_PACKAGE():JPackage("jcpp.nio.file",JPackage::getClazz()){//better class
            classes->push_back(JWatchEvent::getClazz());
        }

        JPackage* JNIO_FILE_PACKAGE::getSuperPackage(){
            return JNIO_PACKAGE::getPackage();
        }

        vector<JPackage*>* JNIO_FILE_PACKAGE::getPackages(){
            if (packages->size()==0){

            }
            return packages;
        }

        static JNIO_FILE_PACKAGE* pack=NULL;

        JNIO_FILE_PACKAGE* JNIO_FILE_PACKAGE::getPackage(){
            if (pack==NULL){
                pack=new JNIO_FILE_PACKAGE();
            }
            return pack;
        }

        JNIO_FILE_PACKAGE::~JNIO_FILE_PACKAGE(){
        }
    }
}



