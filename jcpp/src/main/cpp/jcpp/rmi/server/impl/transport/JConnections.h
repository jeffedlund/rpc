#ifndef JCONNECTIONS_H
#define JCONNECTIONS_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <map>
#include "JSocket.h"
#include "Object.h"
#include "JDataOutputStream.h"
#include "JDataInputStream.h"
#include "JEndPoint.h"
#include "JScheduledFuture.h"
#include "JCPP.h"
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
                    class JTransport;
                    class JCPP_LIBRARY_EXPORT JConnections : public JObject, public JRunnable{
                        protected:
                            JEndPoint* remoteEndPoint;
                            vector<JConnection*>* freeConnectionList;
                            vector<JConnection*>* takenConnectionList;
                            JTransport* transport;
                            jlong connectionTimeout;
                            JScheduledFuture* scheduledFuture;

                            void remove();
                            void launchTimeoutTimer();

                        public:
                            JConnections(JEndPoint* remoteEndPoint, JTransport* transport);
                            static JClass* getClazz();

                            JConnection* createConnection();
                            jlong getConnectionTimeout();
                            void freeAll();
                            void killAll();
                            JEndPoint* getRemoteEndPoint();
                            JTransport* getTransport();
                            void free(JConnection* connection);
                            void kill(JConnection* connection);
                            virtual void run();
                            JString toString();
                            virtual ~JConnections();
                    };
                }
            }
        }
    }
}


#endif // JCONNECTIONS_H
