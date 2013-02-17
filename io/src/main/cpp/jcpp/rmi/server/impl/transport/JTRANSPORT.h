#ifndef JTRANSPORT_H
#define JTRANSPORT_H

#include "JIMPL.h"
#include "JEndPoint.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::impl;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JTRANSPORT : public JPackage{
                    protected:
                        JTRANSPORT();

                    public:
                        JPackage* getSuperPackage();

                        vector<JPackage*>* getPackages();

                        static JTRANSPORT* getPackage();
                    };
                }
            }
        }
    }
}

#endif // JTRANSPORT_H
