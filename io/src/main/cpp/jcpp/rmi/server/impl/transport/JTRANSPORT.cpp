#include "JTRANSPORT.h"
#include "JCPP.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    JTRANSPORT::JTRANSPORT():JPackage("jcpp.rmi.server.impl.transport",JPackage::getClazz()){
                        classes->push_back(JEndPoint::getClazz());
                    }

                    JPackage* JTRANSPORT::getSuperPackage(){
                        return JIMPL::getPackage();
                    }

                    vector<JPackage*>* JTRANSPORT::getPackages(){
                        if (packages->size()==0){
                        }
                        return packages;
                    }

                    static JTRANSPORT* tra=NULL;

                    JTRANSPORT* JTRANSPORT::getPackage(){
                        if (tra==NULL){
                            tra=new JTRANSPORT();
                        }
                        return tra;
                    }
                }
            }
        }
    }
}


