#ifndef JLOGGING_PACKAGE_H
#define JLOGGING_PACKAGE_H

#include "JPackage.h"
#include "JUTIL.h"
#include "JCPP.h"
#include "JConsoleHandler.h"
#include "JErrorManager.h"
#include "JFilter.h"
#include "JFormatter.h"
#include "JHandler.h"
#include "JLevel.h"
#include "JLogger.h"
#include "JLogManager.h"
#include "JLogRecord.h"
#include "JMemoryHandler.h"
#include "JSimpleFormatter.h"
#include "JSocketHandler.h"
#include "JStreamHandler.h"
#include "JXMLFormatter.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace logging{
            class JCPP_LIBRARY_EXPORT JLOGGING_PACKAGE : public JPackage{
            protected:
                JLOGGING_PACKAGE();

            public:
                JPackage* getSuperPackage();

                vector<JPackage*>* getPackages();

                static JLOGGING_PACKAGE* getPackage();

                virtual ~JLOGGING_PACKAGE();
            };
        }
    }
}

#endif // JLOGGING_PACKAGE_H
