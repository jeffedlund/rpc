#ifndef JCONNECTION_PACKAGE_H
#define JCONNECTION_PACKAGE_H

#include "JIMPL.h"
#include "JServer.h"
#include "JIGC.h"
#include "JConnectionConfiguration.h"
#include "JConnectionException.h"
#include "JConnectionInputStream.h"
#include "JConnectionOutputStream.h"
#include "JConnectionTransportDispatcher.h"
#include "JGC.h"
#include "JGCClient.h"
#include "JGCClientEndPointInfo.h"
#include "JGCEndPointInfo.h"
#include "JIGCClient.h"
#include "JIGCClientListener.h"
#include "JIGCClientProxy.h"
#include "JIGCProxy.h"
#include "JIInvocationExceptionHandler.h"
#include "JIInvocationListener.h"
#include "JILifecycle.h"
#include "JINotExportedObjectListener.h"
#include "JInvoker.h"
#include "JIRegistry.h"
#include "JIRegistryProxy.h"
#include "JIServer.h"
#include "JIServerProxy.h"
#include "JMethodDigester.h"
#include "JObjectHandler.h"
#include "JObjectInformation.h"
#include "JObjectInformations.h"
#include "JObjectPointer.h"
#include "JRegistry.h"
#include "JCPP.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JServer;
                    class JCPP_LIBRARY_EXPORT JCONNECTION_PACKAGE : public JPackage{
                    protected:
                        JCONNECTION_PACKAGE();

                    public:
                        JPackage* getSuperPackage();

                        vector<JPackage*>* getPackages();

                        static JCONNECTION_PACKAGE* getPackage();

                        virtual ~JCONNECTION_PACKAGE();
                    };
                }
            }
        }
    }
}

#endif // JCONNECTION_PACKAGE_H
