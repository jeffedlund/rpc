#include "JIMPL.h"
#include "JCPP_PACKAGE.h"
#include "JPackage.h"
#include "JGATEWAY.h"
#include "JSERVER_PACKAGE.h"
#include "JTRANSPORT_PACKAGE.h"
#include "JCONNECTION_PACKAGE.h"
using namespace jcpp::lang;
using namespace jcpp::rmi::server;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::transport;
using namespace jcpp::rmi::server::impl::connection;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                JIMPL::JIMPL():JPackage("jcpp.rmi.server.impl",JPackage::getClazz()){
                }

                JPackage* JIMPL::getSuperPackage(){
                    return JSERVER_PACKAGE::getPackage();
                }

                vector<JPackage*>* JIMPL::getPackages(){
                    if (packages->size()==0){
                        packages->push_back(JGATEWAY::getPackage());
                        packages->push_back(JTRANSPORT_PACKAGE::getPackage());
                        packages->push_back(JCONNECTION_PACKAGE::getPackage());
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

                JIMPL::~JIMPL(){
                }
            }
        }
    }
}
