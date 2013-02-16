#include "JGATEWAY.h"
#include "JCPP.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    JGATEWAY::JGATEWAY():JPackage("jcpp.rmi.server.impl.gateway",JPackage::getClazz()){
                        classes->push_back(JAddress::getClazz());
                        classes->push_back(JRoute::getClazz());
                    }

                    JPackage* JGATEWAY::getSuperPackage(){
                        return JIMPL::getPackage();
                    }

                    vector<JPackage*>* JGATEWAY::getPackages(){
                        if (packages->size()==0){
                        }
                        return packages;
                    }

                    static JGATEWAY* gateway=NULL;

                    JGATEWAY* JGATEWAY::getPackage(){
                        if (gateway==NULL){
                            gateway=new JGATEWAY();
                        }
                        return gateway;
                    }
                }
            }
        }
    }
}


