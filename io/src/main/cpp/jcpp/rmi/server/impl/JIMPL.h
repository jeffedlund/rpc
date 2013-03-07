#ifndef JIMPL_H
#define JIMPL_H

#include "JSERVER_PACKAGE.h"
#include "JCPP.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{

                class JCPP_LIBRARY_EXPORT JIMPL : public JPackage{
                protected:
                    JIMPL();

                public:
                    JPackage* getSuperPackage();

                    vector<JPackage*>* getPackages();

                    static JIMPL* getPackage();

                    virtual ~JIMPL();
                };
            }
        }
    }
}

#endif // JIMPL_H
