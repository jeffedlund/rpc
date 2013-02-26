#ifndef JINVOKER_H
#define JINVOKER_H

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
                    class JInvoker : public JObject, public JSerializable{
                        protected:
                            JObjectInformations* objectInformations;
                            JObjectPointer* objectPointer;

                        public:
                            JInvoker();
                            JInvoker(JObjectInformations* objectInformations, JObjectPointer* objectPointer);
                            static JClass* getClazz();
                            void setObjectPointer(JObjectPointer* o);
                            JObjectPointer* getObjectPointer();
                            void setObjectInformations(JObjectInformations* objectInformations);
                            JObjectInformations* getObjectInformations();
                            JObject* invoke(JMethod* method, vector<JObject*>* args);
                            virtual ~JInvoker();
                    };
                }
            }
        }
    }
}
#endif // JINVOKER_H
