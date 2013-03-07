#ifndef JUTIL_H
#define JUTIL_H

#include "JArrayList.h"
#include "JCollection.h"
#include "JHashtable.h"
#include "JAbstractCollection.h"
#include "JArrayList.h"
#include "JCollection.h"
#include "JList.h"
#include "JTimer.h"
#include "JTimerTask.h"
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
