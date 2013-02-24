#ifndef JOBJECTINFORMATION_H
#define JOBJECTINFORMATION_H

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
#include "JGCEndPointInfo.h"
#include "JILifecycle.h"
#include "JObjectHandler.h"
#include "JGC.h"
#include "JObjectInformations.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JILifecycle;
                    class JObjectHandler;
                    class JGC;
                    class JObjectInformations;
                    class JObjectInformation: public JObject{
                    protected:
                        JString* id;
                        JObject* object;
                        JILifecycle* lifecycle;
                        JObjectHandler* objectHandler;
                        map<JEndPoint*, JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>* exportedEndPoints;
                        JObjectInformations* objectInformations;

                    public:
                        JObjectInformation(JString* id, JObject* object, vector<JClass*>* interfaces, JObjectInformations* objectInformations, JILifecycle* lifecycle, JGC* gc);
                        static JClass* getClazz();
                        JObject* getObject();
                        JString* getId();
                        JILifecycle* getLifecycle();
                        JObjectHandler* getObjectHandler();
                        void exported();
                        void doExport(JGCEndPointInfo* remoteEndPointInfo);
                        void unexport(JEndPoint* endPoint);
                        void unexport();
                        string toString();
                        ~JObjectInformation();
                    };
                }
            }
        }
    }
}

#endif // JOBJECTINFORMATION_H
