#ifndef JGCENDPOINTINFO_H
#define JGCENDPOINTINFO_H

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
#include "JObjectInformation.h"
#include "JFuture.h"
#include "JScheduledFuture.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::transport;
using namespace jcpp::util::concurrent;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JObjectInformation;
                    class JGCEndPointInfo : public JObject, public JRunnable{
                    protected:
                        map<JString*, JObjectInformation*>* exportedObjects;
                        JFuture* future;
                        bool isRunning;
                        jlong lastPingId;
                        jlong previousPingId;
                        JEndPoint* remoteEndPoint;
                        JScheduledFuture* scheduledFuture;

                    public:
                        JGCEndPointInfo(JEndPoint* remoteEndPoint);
                        static JClass* getClazz();
                        bool isUpdated();
                        JEndPoint* getRemoteEndPoint();
                        void doExport(JObjectInformation* objInfo);
                        void unexport(JObjectInformation* objInfo);
                        void unexport();
                        void update();
                        void ping(JPrimitiveArray* returnPing, JPrimitiveArray* ids);
                        virtual void run();
                        ~JGCEndPointInfo();
                    };
                }
            }
        }
    }
}
#endif // JGCENDPOINTINFO_H
