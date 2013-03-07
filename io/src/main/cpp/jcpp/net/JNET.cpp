#include "JNET.h"
#include "JCPP_PACKAGE.h"

namespace jcpp{
    namespace net{
        JNET::JNET():JPackage("jcpp.net",JPackage::getClazz()){//better class
            classes->push_back(JInet4Address::getClazz());
            classes->push_back(JInet6Address::getClazz());
            classes->push_back(JInetAddress::getClazz());
            classes->push_back(JSocket::getClazz());
            classes->push_back(JServerSocket::getClazz());
        }

        JPackage* JNET::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        vector<JPackage*>* JNET::getPackages(){
            if (packages->size()==0){
            }
            return packages;
        }

        static JNET* jNET=NULL;

        JNET* JNET::getPackage(){
            if (jNET==NULL){
                jNET=new JNET();
            }
            return jNET;
        }

        JNET::~JNET(){
        }
    }
}
