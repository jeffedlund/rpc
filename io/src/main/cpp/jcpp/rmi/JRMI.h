#ifndef JRMI_H
#define JRMI_H

#include "JCPP_PACKAGE.h"
#include "JREFLECT.h"
#include "JCPP.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        class JCPP_LIBRARY_EXPORT JRMI : public JPackage{
        protected:
            JRMI();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JRMI* getPackage();

            virtual ~JRMI();
        };
    }
}

#endif // JRMI_H
