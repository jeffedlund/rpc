#ifndef JGCCLIENT_H
#define JGCCLIENT_H

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
#include "JGCEndPointInfo.h"
#include "JGCClientEndPointInfo.h"
#include "JIGCClientListener.h"
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
                    class JGCClientEndPointInfo;
                    class JGCClient : public JObject, public JIGCClient{
                        protected:
                            map<JEndPoint*, JGCClientEndPointInfo*,JEndPoint::POINTER_COMPARATOR>* endPointInfos;
                            JIGCClientListener* gcClientListener;
                            JServer* localServer;

                        public:
                            JGCClient(JServer* localServer, JIGCClientListener* gcClientListener);
                            JPrimitiveArray* getEndPoints();
                            void add(map<JObjectPointer*, JObject*>* objectPointers);
                            void remove(JEndPoint* endPoint);
                            void unexport();
                            JIGCClientListener* getGCClientListener();
                            static JClass* getClazz();
                            ~JGCClient();
                    };
                }
            }
        }
    }
}
#endif // JGCCLIENT_H