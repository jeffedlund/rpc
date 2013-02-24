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
                        JFuture* future;
                        JIGC* gc;
                        int gcExceptionCount;
                        bool isRunning;
                        map<JString*, JObject*>* objects;
                        JEndPoint* remoteEndPoint;
                        JScheduledFuture* scheduledFuture;
                        JThrowable* throwable;
                        JConnections* connections;

                    public:
                        JGCClientEndPointInfo(JEndPoint* remoteEndPoint);
                        static JClass* getClazz();
                        void doExport(JString* id, JObject* object);
                        void unexport(JString* id);
                        bool ping();
                        void unexport();
                        virtual void run();
                        ~JGCClientEndPointInfo();
                    };
                }
            }
        }
    }
}
#endif // JGCCLIENTENDPOINTINFO_H
