#ifndef JTRANSPORT_PACKAGE_H
#define JTRANSPORT_PACKAGE_H

#include "JIMPL.h"
#include "JConnection.h"
#include "JEndPoint.h"
#include "JITransportDispatcher.h"
#include "JITransportRouter.h"
#include "JTransport.h"
#include "JTransportConstants.h"
#include "JTransportRouter.h"
#include "JConnectionHeaderReader.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::impl;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JTRANSPORT_PACKAGE : public JPackage{
                    protected:
                        JTRANSPORT_PACKAGE();

                    public:
                        JPackage* getSuperPackage();

                        vector<JPackage*>* getPackages();

                        static JTRANSPORT_PACKAGE* getPackage();

                        virtual ~JTRANSPORT_PACKAGE();
                    };
                }
            }
        }
    }
}

#endif // JTRANSPORT_H
