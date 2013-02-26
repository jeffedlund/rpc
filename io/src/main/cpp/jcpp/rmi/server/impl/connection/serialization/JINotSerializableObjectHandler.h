#ifndef JINOTSERIALIZABLEOBJECTHANDLER_H
#define JINOTSERIALIZABLEOBJECTHANDLER_H

#include "JObject.h"
#include "JClass.h"
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    namespace serialization{
                        class JINotSerializableObjectHandler : public JInterface{
                        public:
                            static JClass* getClazz();
                            virtual JObject* handleNotSerializableObject(JObject* obj)=0;
                            virtual ~JINotSerializableObjectHandler();
                        };
                    }
                }
            }
        }
    }
}

#endif // JINOTSERIALIZABLEOBJECTHANDLER_H
