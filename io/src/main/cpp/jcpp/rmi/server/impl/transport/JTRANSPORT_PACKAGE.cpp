#include "JTRANSPORT_PACKAGE.h"
#include "JCPP.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    JTRANSPORT_PACKAGE::JTRANSPORT_PACKAGE():JPackage("jcpp.rmi.server.impl.transport",JPackage::getClazz()){
                        classes->push_back(JConnection::getClazz());
                        classes->push_back(JConnectionHeaderReader::getClazz());
                        classes->push_back(JConnections::getClazz());
                        classes->push_back(JEndPoint::getClazz());
                        classes->push_back(JITransportDispatcher::getClazz());
                        classes->push_back(JITransportRouter::getClazz());
                        classes->push_back(JTransport::getClazz());
                        classes->push_back(JTransportConfiguration::getClazz());
                        classes->push_back(JTransportRouter::getClazz());
                    }

                    JPackage* JTRANSPORT_PACKAGE::getSuperPackage(){
                        return JIMPL::getPackage();
                    }

                    vector<JPackage*>* JTRANSPORT_PACKAGE::getPackages(){
                        if (packages->size()==0){
                        }
                        return packages;
                    }

                    static JTRANSPORT_PACKAGE* tra=NULL;

                    JTRANSPORT_PACKAGE* JTRANSPORT_PACKAGE::getPackage(){
                        if (tra==NULL){
                            tra=new JTRANSPORT_PACKAGE();
                        }
                        return tra;
                    }
                }
            }
        }
    }
}


