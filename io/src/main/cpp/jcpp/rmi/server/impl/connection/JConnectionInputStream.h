#ifndef JCONNECTIONINPUTSTREAM_H
#define JCONNECTIONINPUTSTREAM_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JAddress.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JEndPoint.h"
#include "JException.h"
#include "JBoolean.h"
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
                    class JConnectionInputStream : public JObjectInputStream{
                    protected:
                        JObjectInformations* objectInformations;
                        map<JObjectPointer*, JObject*>* gcObjectPointers;
                        JEndPoint* remoteEndPoint;

                    public:
                        JConnectionInputStream(JInputStream* in, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint);
                        static JClass* getClazz();
                        void done();
                        virtual JObject* resolveObject(JObject* obj);
                        virtual ~JConnectionInputStream();
                    };
                }
            }
        }
    }
}

#endif // JCONNECTIONINPUTSTREAM_H
