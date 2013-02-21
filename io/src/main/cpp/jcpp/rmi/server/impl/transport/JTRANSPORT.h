#ifndef JTRANSPORT_H
#define JTRANSPORT_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <map>
#include "JSocket.h"
#include "Object.h"
#include "JDataOutputStream.h"
#include "JDataInputStream.h"
#include "JExecutorService.h"
#include "JEndPoint.h"
#include "JConnections.h"
#include "JScheduledExecutorService.h"
#include "JITransportRouter.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::net;
using namespace jcpp::util::concurrent;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JConnection;
                    class JConnections;
                    class JConnectionHeaderReader;
                    class JITransportDispatcher;
                    class JTransport : public JObject, public JRunnable{
                        protected:
                            JExecutorService* executorService;
                            JFuture* future;
                            JEndPoint* localEndPoint;
                            map<JEndPoint*,JConnections*>* remoteConnectionsMap;
                            vector<JConnectionHeaderReader*>* connectionReaders;
                            JScheduledExecutorService* scheduledExecutorService;
                            JServerSocket* serverSocket;
                            JITransportRouter* transportRouter;
                            JITransportDispatcher* transportDispatcher;

                        public:
                            JTransport(JEndPoint* localEndPoint,JITransportRouter* transportRouter,JITransportDispatcher* transportDispatcher,JExecutorService* executorService,JScheduledExecutorService* scheduledExecutorService);
                            static JClass* getClazz();

                            JConnections* getConnections(JEndPoint* remoteEndPoint);
                            JEndPoint* getLocalEndPoint();
                            JScheduledExecutorService* getScheduledExecutorService();
                            JITransportDispatcher* getTransportDispatcher();
                            JITransportRouter* getTransportRouter();
                            void startExport();
                            virtual void run();
                            void stopExport();
                            void remove(JConnectionHeaderReader* reader);
                            void remove(JConnections* connections);
                            ~JTransport();
                    };
                }
            }
        }
    }
}



#endif // JTRANSPORT_H
