#include "JSERVER.h"
#include "JCPP.h"
#include "JIMPL.h"
using namespace jcpp::rmi::server::impl;

namespace jcpp{
    namespace rmi{
        namespace server{
            JSERVER::JSERVER():JPackage("jcpp.rmi.server",JPackage::getClazz()){
            }

            JPackage* JSERVER::getSuperPackage(){
                return JRMI::getPackage();
            }

            vector<JPackage*>* JSERVER::getPackages(){
                if (packages->size()==0){
                    packages->push_back(JIMPL::getPackage());
                }
                return packages;
            }

            static JSERVER* server=NULL;

            JSERVER* JSERVER::getPackage(){
                if (server==NULL){
                    server=new JSERVER();
                }
                return server;
            }
        }
    }
}

