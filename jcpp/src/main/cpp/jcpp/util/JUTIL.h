#ifndef JUTIL_H
#define JUTIL_H

#include "JAbstractCollection.h"
#include "JAbstractList.h"
#include "JAbstractMap.h"
#include "JAbstractQueue.h"
#include "JAbstractSet.h"
#include "JArrayList.h"
#include "JCollection.h"
#include "JCollections.h"
#include "JComparator.h"
#include "JConcurrentModificationException.h"
#include "JDictionary.h"
#include "JEnumeration.h"
#include "JHashMap.h"
#include "JHashSet.h"
#include "JHashtable.h"
#include "JIdentityHashMap.h"
#include "JIterator.h"
#include "JListIterator.h"
#include "JList.h"
#include "JMap.h"
#include "JNoSuchElementException.h"
#include "JQueue.h"
#include "JRandomAccess.h"
#include "JSet.h"
#include "JTimer.h"
#include "JTimerTask.h"
#include "JVector.h"
#include "JPackage.h"
#include "JCONCURRENT.h"
#include "JCPP.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JUTIL : public JPackage{
        protected:
            JUTIL();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JUTIL* getPackage();

            virtual ~JUTIL();
        };
    }
}

#endif // JUTIL_H
