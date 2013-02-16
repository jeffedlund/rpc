#ifndef JRMI_H
#define JRMI_H

#include "JCPP.h"
#include "JREFLECT.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        class JRMI : public JPackage{
        protected:
            JRMI();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JRMI* getPackage();
        };
    }
}

#endif // JRMI_H
