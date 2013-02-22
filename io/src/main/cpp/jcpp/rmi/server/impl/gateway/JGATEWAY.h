#ifndef JGATEWAY_H
#define JGATEWAY_H

#include "JIMPL.h"
#include "JAddress.h"
#include "JRoute.h"
#include "JGatewayCompressionInputStream.h"
#include "JGatewayCompressionOutputStream.h"
#include "JGatewayConfiguration.h"
#include "JGatewayInputStream.h"
#include "JGatewayOutputStream.h"
#include "JGatewayServerSocket.h"
#include "JGatewaySocket.h"
#include "JGatewaySocketFactory.h"
#include "JIGatewaySocket.h"
using namespace jcpp;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::impl;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGATEWAY : public JPackage{
                    protected:
                        JGATEWAY();

                    public:
                        JPackage* getSuperPackage();

                        vector<JPackage*>* getPackages();

                        static JGATEWAY* getPackage();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAY_H
