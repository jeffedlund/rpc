#include "JLOGGING_PACKAGE.h"
#include "JUTIL.h"
using namespace jcpp::util;

namespace jcpp{
    namespace util{
        namespace logging{
            JLOGGING_PACKAGE::JLOGGING_PACKAGE():JPackage("jcpp.util.logging",JPackage::getClazz()){
                classes->push_back(JConsoleHandler::getClazz());
                classes->push_back(JErrorManager::getClazz());
                classes->push_back(JFilter::getClazz());
                classes->push_back(JFormatter::getClazz());
                classes->push_back(JHandler::getClazz());
                classes->push_back(JLevel::getClazz());
                classes->push_back(JLogger::getClazz());
                classes->push_back(JLogManager::getClazz());
                classes->push_back(JLogRecord::getClazz());
                classes->push_back(JMemoryHandler::getClazz());
                classes->push_back(JSimpleFormatter::getClazz());
                classes->push_back(JSocketHandler::getClazz());
                classes->push_back(JStreamHandler::getClazz());
                classes->push_back(JXMLFormatter::getClazz());
            }

            JPackage* JLOGGING_PACKAGE::getSuperPackage(){
                return JUTIL::getPackage();
            }

            vector<JPackage*>* JLOGGING_PACKAGE::getPackages(){
                if (packages->size()==0){
                }
                return packages;
            }

            static JLOGGING_PACKAGE* jpackage=NULL;

            JLOGGING_PACKAGE* JLOGGING_PACKAGE::getPackage(){
                if (jpackage==NULL){
                    jpackage=new JLOGGING_PACKAGE();
                }
                return jpackage;
            }

            JLOGGING_PACKAGE::~JLOGGING_PACKAGE(){
            }
        }
    }
}

