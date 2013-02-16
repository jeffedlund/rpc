#include "JRMI.h"
#include "JCPP.h"
#include "JSERVER.h"
using namespace jcpp::rmi::server;

namespace jcpp{
    namespace rmi{
        JRMI::JRMI():JPackage("jcpp.rmi",JPackage::getClazz()){//better class
        }

        JPackage* JRMI::getSuperPackage(){
            return JCPP::getPackage();
        }

        vector<JPackage*>* JRMI::getPackages(){
            if (packages->size()==0){
                packages->push_back(JSERVER::getPackage());
            }
            return packages;
        }

        static JRMI* jRMI=NULL;

        JRMI* JRMI::getPackage(){
            if (jRMI==NULL){
                jRMI=new JRMI();
            }
            return jRMI;
        }
    }
}

