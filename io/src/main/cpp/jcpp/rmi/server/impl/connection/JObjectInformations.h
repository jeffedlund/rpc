#ifndef JOBJECTINFORMATIONS_H
#define JOBJECTINFORMATIONS_H

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
#include "JException.h"
#include "JBoolean.h"
#include "JIRegistry.h"
#include "JIGCClient.h"
#include "JIGC.h"
#include "JILifecycle.h"
#include "JTransport.h"
#include "JIInvocationListener.h"
#include "JMethodDigester.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JServer;
                    class JGCClient;
                    class JGC;
                    class JObjectInformation;
                    class JILifecycle;
                    class JMethodDigester;
                    class JObjectInformations: public JObject{
                    protected:
                        map<JString*, JObjectInformation*,JString::POINTER_COMPARATOR>* idMap;
                        map<JObject*, JObjectInformation*>* objectMap;
                        JTransport* transport;
                        JILifecycle* lifecycle;
                        JIInvocationListener* invocationListener;
                        JServer* server;
                        JGC* gc;
                        JGCClient* gcClient;
                        JMethodDigester* methodDigester;

                    public:
                        JObjectInformations(JILifecycle* lifecycle, JServer* server, JGC* gc, JGCClient* gcClient,JIInvocationListener* invocationListener);
                        static JClass* getClazz();

                        void setTransport(JTransport* transport);
                        JTransport* getTransport();
                        JServer* getServer();
                        JGC* getGC();
                        JGCClient* getGCClient();
                        JIInvocationListener* getInvocationListener();
                        JMethodDigester* getMethodDigester();
                        void doExport(JString* id, JObject* object, vector<JClass*>* interfaces);
                        JObjectInformation* unexport(JString* id);
                        JObjectInformation* unexport(JObject* object);
                        void unexport();
                        vector<JString*>* list();
                        JObjectInformation* getObjectInformation(JString* id);
                        JObjectInformation* getObjectInformation(JObject* object);
                        JObjectInformation* remove(JString* id);
                        virtual ~JObjectInformations();
                    };
                }
            }
        }
    }
}

#endif // JOBJECTINFORMATIONS_H
