#ifndef JDEFAULTNOTSERIALIZABLEOBJECTHANDLER_H
#define JDEFAULTNOTSERIALIZABLEOBJECTHANDLER_H

#include "JObject.h"
#include "JClass.h"
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JINotSerializableObjectHandler.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    namespace serialization{
                        class JDefaultNotSerializableObjectHandler : public JObject, JINotSerializableObjectHandler{
                        public:
                            JDefaultNotSerializableObjectHandler();
                            static JClass* getClazz();
                            virtual JObject* handleNotSerializableObject(JObject* obj);
                            virtual ~JDefaultNotSerializableObjectHandler();
                        };
                    }
                }
            }
        }
    }
}
#endif // JDEFAULTNOTSERIALIZABLEOBJECTHANDLER_H
