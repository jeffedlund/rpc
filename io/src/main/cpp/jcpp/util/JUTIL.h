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
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        class JUTIL : public JPackage{
        protected:
            JUTIL();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JUTIL* getPackage();
        };
    }
}

#endif // JUTIL_H
