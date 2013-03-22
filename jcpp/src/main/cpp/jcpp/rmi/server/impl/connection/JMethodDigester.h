#ifndef JMETHODDIGESTER_H
#define JMETHODDIGESTER_H

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
#include "JCPP.h"
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
                    class JCPP_LIBRARY_EXPORT JMethodDigester : public JObject{
                        protected:
                            map<JClass*, map<long, JMethod*>*>* digestToMethodMap;
                            map<JClass*, map<JMethod*, long>*>* methodToDigestMap;
                            void createDigests(JClass* classObject);

                        public:
                            JMethodDigester();
                            static JClass* getClazz();
                            JMethod* getMethodFromDigest(JObject* object, long digest);
                            long getDigestFromMethod(JMethod* method);
                            vector<JMethod*>* getMethods(JObject* object);
                            void clear();
                            virtual ~JMethodDigester();
                    };
                }
            }
        }
    }
}
#endif // JMETHODDIGESTER_H
