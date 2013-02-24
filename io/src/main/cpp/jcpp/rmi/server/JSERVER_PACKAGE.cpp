#include "JSERVER_PACKAGE.h"
#include "JCPP.h"
#include "JIMPL.h"
using namespace jcpp::rmi::server::impl;

namespace jcpp{
    namespace rmi{
        namespace server{
            JSERVER_PACKAGE::JSERVER_PACKAGE():JPackage("jcpp.rmi.server",JPackage::getClazz()){
            }

            JPackage* JSERVER_PACKAGE::getSuperPackage(){
                return JRMI::getPackage();
            }

            vector<JPackage*>* JSERVER_PACKAGE::getPackages(){
                if (packages->size()==0){
                    packages->push_back(JIMPL::getPackage());
                }
                return packages;
            }

            static JSERVER_PACKAGE* server=NULL;

            JSERVER_PACKAGE* JSERVER_PACKAGE::getPackage(){
                if (server==NULL){
                    server=new JSERVER_PACKAGE();
                }
                return server;
            }
        }
    }
}

