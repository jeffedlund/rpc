#include "JUTIL.h"
#include "JCPP_PACKAGE.h"
#include "JLOGGING_PACKAGE.h"
using namespace jcpp::util::concurrent;
using namespace jcpp::util::logging;

namespace jcpp{
    namespace util{
        JUTIL::JUTIL():JPackage("jcpp.util",JPackage::getClazz()){//better class
            classes->push_back(JAbstractCollection::getClazz());
            classes->push_back(JAbstractList::getClazz());
            classes->push_back(JAbstractMap::getClazz());
            classes->push_back(JAbstractQueue::getClazz());
            classes->push_back(JAbstractSet::getClazz());
            classes->push_back(JArrayList::getClazz());
            classes->push_back(JCollection::getClazz());
            classes->push_back(JCollections::getClazz());
            classes->push_back(JComparator::getClazz());
            classes->push_back(JConcurrentModificationException::getClazz());
            classes->push_back(JDictionary::getClazz());
            classes->push_back(JEnumeration::getClazz());
            classes->push_back(JHashMap::getClazz());
            classes->push_back(JHashtable::getClazz());
            classes->push_back(JHashSet::getClazz());
            classes->push_back(JIdentityHashMap::getClazz());
            classes->push_back(JIterator::getClazz());
            classes->push_back(JList::getClazz());
            classes->push_back(JListIterator::getClazz());
            classes->push_back(JMap::getClazz());
            classes->push_back(JNoSuchElementException::getClazz());
            classes->push_back(JQueue::getClazz());
            classes->push_back(JRandomAccess::getClazz());
            classes->push_back(JSet::getClazz());
            classes->push_back(JTimer::getClazz());
            classes->push_back(JTimerTask::getClazz());
            classes->push_back(JVector::getClazz());
        }

        JPackage* JUTIL::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        vector<JPackage*>* JUTIL::getPackages(){
            if (packages->size()==0){
                packages->push_back(JCONCURRENT::getPackage());
                packages->push_back(JLOGGING_PACKAGE::getPackage());
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

        JUTIL::~JUTIL(){
        }
    }
}
