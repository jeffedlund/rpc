#include "JUTIL.h"
#include "JCPP.h"

namespace jcpp{
    namespace util{
        JUTIL::JUTIL():JPackage("jcpp.util",JPackage::getClazz()){//better class
            classes->push_back(JAbstractCollection::getClazz());
            classes->push_back(JAbstractList::getClazz());
            classes->push_back(JArrayList::getClazz());
            classes->push_back(JCollection::getClazz());
            classes->push_back(JList::getClazz());
            //TODO JCollection::
            //TODO JHashtable::getC
        }

        JPackage* JUTIL::getSuperPackage(){
            return JCPP::getPackage();
        }

        vector<JPackage*>* JUTIL::getPackages(){
            if (packages->size()==0){
            }
            return packages;
        }

        static JUTIL* jutil=NULL;

        JUTIL* JUTIL::getPackage(){
            if (jutil==NULL){
                jutil=new JUTIL();
            }
            return jutil;
        }
    }
}
