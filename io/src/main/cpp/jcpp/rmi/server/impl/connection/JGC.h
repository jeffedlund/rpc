#ifndef JGC_H
#define JGC_H

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
#include "JObjectInformation.h"
#include "JObjectPointer.h"
#include "JConnectionConfiguration.h"
#include "JGCEndPointInfo.h"
#include "JExecutorService.h"
#include "JScheduledExecutorService.h"
#include "JGCEndPointInfo.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::util::concurrent;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JGCEndPointInfo;
                    class JObjectInformation;
                    class JGC : public JObject, public JIGC{
                        protected:
                            JConnectionConfiguration* connectionConfiguration;
                            map<JEndPoint*, JGCEndPointInfo*,JEndPoint::POINTER_COMPARATOR>* endPointInfos;
                            JExecutorService* executorService;
                            JScheduledExecutorService* scheduledExecutorService;

                        public:
                            JGC(JExecutorService* executorService, JScheduledExecutorService* scheduledExecutorService, JConnectionConfiguration* connectionConfiguration);
                            static JClass* getClazz();
                            JPrimitiveArray* getExportedEndPoints();
                            JScheduledExecutorService* getScheduledExecutorService();
                            JConnectionConfiguration* getConnectionConfiguration();
                            JPrimitiveArray* ping(JEndPoint* endPoint, JPrimitiveArray* ids);
                            void doExport(vector<JObjectInformation*>* objInfoSet, JEndPoint* endPoint);
                            void unexport(JEndPoint* endPoint);
                            void unexport();
                            void endPointDead(JEndPoint* endPoint);
                            void doExport(JObjectInformation* objInfo, JEndPoint* endPoint);
                            void remove(JEndPoint* e);
                            ~JGC();
                    };
                }
            }
        }
    }
}
#endif // JGC_H
