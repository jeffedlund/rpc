#include "JIMPL.h"
#include "JCPP.h"
#include "JPackage.h"
#include "JGATEWAY.h"
#include "JTRANSPORT.h"
using namespace jcpp::lang;
using namespace jcpp::rmi::server;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                JIMPL::JIMPL():JPackage("jcpp.rmi.server.impl",JPackage::getClazz()){
                }

                JPackage* JIMPL::getSuperPackage(){
                    return JSERVER::getPackage();
                }

                vector<JPackage*>* JIMPL::getPackages(){
                    if (packages->size()==0){
                        packages->push_back(JGATEWAY::getPackage());
                        packages->push_back(JTRANSPORT::getPackage());
                    }
                    return packages;
                }

                static JIMPL* jImpl=NULL;

                JIMPL* JIMPL::getPackage(){
                    if (jImpl==NULL){
                        jImpl=new JIMPL();
                    }
                    return jImpl;
                }
            }
        }
    }
}