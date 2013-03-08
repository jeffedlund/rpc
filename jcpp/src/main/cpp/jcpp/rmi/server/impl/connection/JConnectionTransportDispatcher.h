#ifndef JCONNECTIONTRANSPORTDISPATCHER_H
#define JCONNECTIONTRANSPORTDISPATCHER_H

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
#include "JITransportDispatcher.h"
#include "JObjectInformations.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JCPP_LIBRARY_EXPORT JConnectionTransportDispatcher : public JObject, public JITransportDispatcher{
                    protected:
                        JObjectInformations* objectInformations;
                    public:
                        class InvocationResult{
                        protected:
                            JObject* object;
                            JMethod* method;
                            JObject* result;
                            bool exceptionThrown;
                        public:
                            InvocationResult(JObject* object, JMethod* method, JObject* result, bool exceptionThrown);
                            JObject* getObject();
                            JMethod* getMethod();
                            JObject* getResult();
                            bool isExceptionThrown();
                        };

                        JConnectionTransportDispatcher(JObjectInformations* objectInformations);
                        static JClass* getClazz();
                        virtual void dispatch(JEndPoint* fromEndPoint, JEndPoint* toEndPoint, JConnection* connection);
                        InvocationResult* invokeMethod(JString* id, jlong digest, vector<JObject*>* args, JEndPoint* endPoint);
                        virtual ~JConnectionTransportDispatcher();
                    };
                }
            }
        }
    }
}
#endif // JCONNECTIONTRANSPORTDISPATCHER_H
