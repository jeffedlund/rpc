#ifndef JSERVER_H
#define JSERVER_H

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
#include "JIServer.h"
#include "JTransport.h"
#include "JObjectInformations.h"
#include "JINotExportedObjectListener.h"
#include "JINotSerializableObjectHandler.h"
#include "JConnectionConfiguration.h"
#include "JObjectHandler.h"
#include "JIGCClientListener.h"
#include "JGC.h"
#include "JGCClient.h"
#include "JObjectInformations.h"
#include "JObjectInformation.h"
#include "JRegistry.h"
#include "JIInvocationExceptionHandler.h"
#include "JIInvocationListener.h"
#include "JConnectionTransportDispatcher.h"
#include "JClassLoader.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;
using namespace jcpp::rmi::server::impl::connection::serialization;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JGC;
                    class JGCClient;
                    class JConnectionTransportDispatcher;
                    class JCPP_LIBRARY_EXPORT JServer : public JObject, public JIServer, public JILifecycle, public JIGCClientListener, public JIInvocationListener{
                    protected:
                        JClassLoader* classLoader;
                        JEndPoint* endPoint;
                        JIRegistry* iregistry;
                        JRegistry* registry;
                        JTransport* transport;
                        JObjectInformations* objectInformations;
                        vector<JILifecycle*>* lifecycles;
                        vector<JIGCClientListener*>* gcClientListeners;
                        vector<JIInvocationListener*>* invocationListeners;
                        JINotExportedObjectListener* notExportedObjectListener;
                        JINotSerializableObjectHandler* notSerializableObjectHandler;
                        JGC* gc;
                        JGCClient* gcClient;
                        JScheduledExecutorService* scheduledExecutorService;
                        JExecutorService* executorService;
                        JConnectionTransportDispatcher* connectionTransportDispatcher;
                        JConnectionConfiguration* connectionConfiguration;
                        JIInvocationExceptionHandler*  invocationExceptionHandler;
                        static JObjectHandler* getObjectHandlerFromProxy(JObject* object);
                        static JServer* getServerFromExportedObject(JObject* object);


                    public:
                        JServer(JEndPoint* endPoint, JITransportRouter* transportRouter, JConnectionConfiguration* connectionConfiguration);
                        static JClass* getClazz();

                        static JIServer* getRemoteServer(JObject* object);
                        static JIServer* getLocalServer(JObject* object);
                        static JString* getHost(JObject* object);
                        static JPrimitiveInt* getPort(JObject* object);
                        static JString* getSite(JObject* object);
                        static JEndPoint* getEndPoint(JObject* object);
                        static JString* getId(JObject* object);


                        virtual JObject* lookup(JEndPoint* endPoint, JClass* clazz);
                        virtual JObject* lookup(JString* id, JEndPoint* endPoint, JPrimitiveArray* interfaces);

                        JClassLoader* getClassLoader();
                        void setClassLoader(JClassLoader* classloader);

                        JIRegistry* getIRegistry();
                        JEndPoint* getEndPoint();
                        JIGC* getGC();
                        JIGCClient* getGCClient();
                        JExecutorService* getExecutorService();
                        JScheduledExecutorService* getScheduledExecutorService();
                        JObjectInformations* getObjectInformations();
                        JConnectionTransportDispatcher* getConnectionTransportDispatcher();
                        JConnectionConfiguration* getConnectionConfiguration();
                        JINotExportedObjectListener* getNotExportedObjectListener();
                        void setNotExportedObjectListener(JINotExportedObjectListener* notExportedObjectListener);
                        JINotSerializableObjectHandler* getNotSerializableObjectHandler();
                        void setNotSerializableObjectHandler(JINotSerializableObjectHandler* notSerializableObjectHandler);
                        JIInvocationExceptionHandler* getInvocationExceptionHandler();
                        void setInvocationExceptionHandler(JIInvocationExceptionHandler*);
                        void unexport();

                        void addLifecycle(JILifecycle* lifecycle);
                        void removeLifecycle(JILifecycle* lifecycle);
                        void addGCClientListener(JIGCClientListener* gcClientListener);
                        void removeGCClientListener(JIGCClientListener* gcClientListener);
                        void addInvocationListener(JIInvocationListener* i);
                        void removeInvocationListener(JIInvocationListener* i);

                        virtual void doExport(JObjectInformation* objectInformation, JEndPoint* endPoint);
                        virtual void unexport(JObjectInformation* objectInformation);
                        virtual void doExport(JObjectInformation* objectInformation);
                        virtual void unexport(JObjectInformation* objectInformation, JEndPoint* endPoint);


                        virtual void objectAlive(JEndPoint* endPoint, vector<JObject*>* objects);
                        virtual void objectDead(JEndPoint* endPoint, vector<JObject*>* objects);
                        virtual void objectDead(JEndPoint* endPoint, vector<JObject*>* objects, JThrowable* throwable);
                        virtual void objectMaybeDead(JEndPoint* endPoint, vector<JObject*>* objects, JThrowable* throwable);

                        virtual void invocationSucceeded(JObject* proxy, JMethod* method, vector<JObject*>* args);
                        virtual void invocationFailed(JObject* proxy, JMethod* method, vector<JObject*>* args, JThrowable* e);

                        JString toString();
                        virtual ~JServer();
                    };
                }
            }
        }
    }
}
#endif // JSERVER_H
