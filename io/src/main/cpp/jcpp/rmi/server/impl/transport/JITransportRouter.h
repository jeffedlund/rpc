#ifndef JITRANSPORTROUTER_H
#define JITRANSPORTROUTER_H

#include "JInterface.h"
#include "JClass.h"
#include "JRunnable.h"
#include "JRoute.h"
#include "JEndPoint.h"
#include "JString.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JITransportRouter : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual JRoute* findRoute(JString* localSite, JEndPoint* remoteEndpoint)=0;
                        virtual ~JITransportRouter();
                    };
                }
            }
        }
    }
}

#endif // JITRANSPORTROUTER_H
