#ifndef JCONNECTIONOUTPUTSTREAM_H
#define JCONNECTIONOUTPUTSTREAM_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JAddress.h"
#include "JObjectOutputStream.h"
#include "JObjectOutputStream.h"
#include "JEndPoint.h"
#include "JException.h"
#include "JBoolean.h"
#include "JObjectInformations.h"
#include "JINotSerializableObjectHandler.h"
#include "JINotExportedObjectListener.h"
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
                    class JConnectionOutputStream : public JObjectOutputStream{
                    protected:
                        JEndPoint* remoteEndPoint;
                        JObjectInformations* objectInformations;
                        vector<JObjectInformation*>* exportedObjInfos;

                    public:
                        JConnectionOutputStream(JOutputStream* out, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint);
                        static JClass* getClazz();
                        void done();
                        virtual JObject* replaceObject(JObject* obj);
                        virtual ~JConnectionOutputStream();
                    };
                }
            }
        }
    }
}
#endif // JCONNECTIONOUTPUTSTREAM_H
