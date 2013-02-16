#ifndef JIMPL_H
#define JIMPL_H

#include "JSERVER.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{

                class JIMPL : public JPackage{
                protected:
                    JIMPL();

                public:
                    JPackage* getSuperPackage();

                    vector<JPackage*>* getPackages();

                    static JIMPL* getPackage();
                };
            }
        }
    }
}

#endif // JIMPL_H
