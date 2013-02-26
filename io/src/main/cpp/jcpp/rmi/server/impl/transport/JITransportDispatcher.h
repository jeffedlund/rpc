#ifndef JITRANSPORTDISPATCHER_H
#define JITRANSPORTDISPATCHER_H

#include "JInterface.h"
#include "JClass.h"
#include "JRunnable.h"
#include "JRoute.h"
#include "JEndPoint.h"
#include "JString.h"
#include "JConnection.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JITransportDispatcher : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual void dispatch(JEndPoint* fromEndPoint, JEndPoint* toEndpoint,JConnection* connection)=0;
                        virtual ~JITransportDispatcher();
                    };
                }
            }
        }
    }
}

#endif // JITRANSPORTDISPATCHER_H
