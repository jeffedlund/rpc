#ifndef JGCCLIENTENDPOINTINFO_H
#define JGCCLIENTENDPOINTINFO_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JAddress.h"
#include "JDataInputStream.h"
#include "JDataOutputStream.h"
#include "JEndPoint.h"
#include "JObjectInformations.h"
#include "JObjectPointer.h"
#include "JConnectionConfiguration.h"
#include "JServer.h"
#include "JGCClient.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JGCClientEndPointInfo : public JObject, public JRunnable{
                    protected:
                        JGCClient* gcClient;
                        JServer* localServer;
                        JFuture* future;
                        JIGC* gc;
                        int gcExceptionCount;
                        bool bIsRunning;
                        map<JString*, JObject*,JString::POINTER_COMPARATOR>* objects;
                        JEndPoint* remoteEndPoint;
                        JScheduledFuture* scheduledFuture;
                        JThrowable* throwable;
                        JConnections* connections;

                    public:
                        JGCClientEndPointInfo(JGCClient* gcClient,JServer* localServer,JEndPoint* remoteEndPoint);
                        static JClass* getClazz();
                        void doExport(JString* id, JObject* object);
                        void unexport(JString* id);
                        bool ping();
                        void unexport();
                        bool isRunning();
                        void setRunning(bool);
                        vector<JObject*>* getObjects();
                        virtual void run();
                        virtual ~JGCClientEndPointInfo();
                    };
                }
            }
        }
    }
}
#endif // JGCCLIENTENDPOINTINFO_H
