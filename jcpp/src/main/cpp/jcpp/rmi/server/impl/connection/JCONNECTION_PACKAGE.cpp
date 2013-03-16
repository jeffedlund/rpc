#include "JCONNECTION_PACKAGE.h"
#include "JIMPL.h"
#include "JCONNECTION_SERIALIZATION_PACKAGE.h"
#include "JServer.h"
using namespace jcpp::rmi::server::impl;
using namespace jcpp::rmi::server::impl::connection;
using namespace jcpp::rmi::server::impl::connection::serialization;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    JCONNECTION_PACKAGE::JCONNECTION_PACKAGE():JPackage("jcpp.rmi.server.impl.connection",JPackage::getClazz()){
                        classes->push_back(JIGC::getClazz());
                        classes->push_back(JConnectionConfiguration::getClazz());
                        classes->push_back(JConnectionException::getClazz());
                        classes->push_back(JConnectionInputStream::getClazz());
                        classes->push_back(JConnectionOutputStream::getClazz());
                        classes->push_back(JConnectionTransportDispatcher::getClazz());
                        classes->push_back(JGC::getClazz());
                        classes->push_back(JGCClient::getClazz());
                        classes->push_back(JGCClientEndPointInfo::getClazz());
                        classes->push_back(JGCEndPointInfo::getClazz());
                        classes->push_back(JIGCClient::getClazz());
                        classes->push_back(JIGCClientListener::getClazz());
                        classes->push_back(JIGCClientProxy::getClazz());
                        classes->push_back(JIGCProxy::getClazz());
                        classes->push_back(JIInvocationExceptionHandler::getClazz());
                        classes->push_back(JIInvocationListener::getClazz());
                        classes->push_back(JILifecycle::getClazz());
                        classes->push_back(JINotExportedObjectListener::getClazz());
                        classes->push_back(JInvoker::getClazz());
                        classes->push_back(JIRegistry::getClazz());
                        classes->push_back(JIRegistryProxy::getClazz());
                        classes->push_back(JIServer::getClazz());
                        classes->push_back(JIServerProxy::getClazz());
                        classes->push_back(JMethodDigester::getClazz());
                        classes->push_back(JObjectHandler::getClazz());
                        classes->push_back(JObjectInformation::getClazz());
                        classes->push_back(JObjectInformations::getClazz());
                        classes->push_back(JObjectPointer::getClazz());
                        classes->push_back(JRegistry::getClazz());
                        classes->push_back(JServer::getClazz());
                    }

                    JPackage* JCONNECTION_PACKAGE::getSuperPackage(){
                        return JIMPL::getPackage();
                    }

                    vector<JPackage*>* JCONNECTION_PACKAGE::getPackages(){
                        if (packages->size()==0){
                            packages->push_back(JCONNECTION_SERIALIZATION_PACKAGE::getPackage());
                        }
                        return packages;
                    }

                    static JCONNECTION_PACKAGE* pack=NULL;

                    JCONNECTION_PACKAGE* JCONNECTION_PACKAGE::getPackage(){
                        if (pack==NULL){
                            pack=new JCONNECTION_PACKAGE();
                        }
                        return pack;
                    }

                    JCONNECTION_PACKAGE::~JCONNECTION_PACKAGE(){
                    }
                }
            }
        }
    }
}



