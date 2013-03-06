#include "JCONNECTION_SERIALIZATION_PACKAGE.h"
#include "JIMPL.h"
using namespace jcpp::rmi::server::impl;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    namespace serialization{
                        JCONNECTION_SERIALIZATION_PACKAGE::JCONNECTION_SERIALIZATION_PACKAGE():JPackage("jcpp.rmi.server.impl.connection.serialization",JPackage::getClazz()){
                            classes->push_back(JDefaultNotSerializableObjectHandler::getClazz());
                            classes->push_back(JINotSerializableObjectHandler::getClazz());
                            classes->push_back(JNullNotSerializableObjectHandler::getClazz());
                        }

                        JPackage* JCONNECTION_SERIALIZATION_PACKAGE::getSuperPackage(){
                            return JCONNECTION_PACKAGE::getPackage();
                        }

                        vector<JPackage*>* JCONNECTION_SERIALIZATION_PACKAGE::getPackages(){
                            if (packages->size()==0){
                            }
                            return packages;
                        }

                        static JCONNECTION_SERIALIZATION_PACKAGE* pack=NULL;

                        JCONNECTION_SERIALIZATION_PACKAGE* JCONNECTION_SERIALIZATION_PACKAGE::getPackage(){
                            if (pack==NULL){
                                pack=new JCONNECTION_SERIALIZATION_PACKAGE();
                            }
                            return pack;
                        }

                        JCONNECTION_SERIALIZATION_PACKAGE::~JCONNECTION_SERIALIZATION_PACKAGE(){
                        }
                    }
                }
            }
        }
    }
}




