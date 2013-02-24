#ifndef JOBJECTPOINTER_H
#define JOBJECTPOINTER_H

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
                    class JObjectPointer : public JObject, public JSerializable{
                        protected:
                            JEndPoint* endPoint;
                            JString* id;

                        public:
                            JObjectPointer();
                            JObjectPointer(JEndPoint* endPoint, JString* id);
                            bool operator==(JObject &other);
                            static JClass* getClazz();
                            JEndPoint* getEndPoint();
                            void setEndPoint(JEndPoint* endPoint);
                            JString* getId();
                            void setId(JString* id);
                            string toString();
                            ~JObjectPointer();
                    };
                }
            }
        }
    }
}

#endif // JOBJECTPOINTER_H
